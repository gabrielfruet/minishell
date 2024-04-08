#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "../colors.h"
#include "sys/wait.h"
#include "redirection.h"
#include "list.h"

const char REDIR_CHARS[] = "|";

redirlist_t* redirlist_alloc(char* to_exec, redir_enum redir_type) {
    redirlist_t* redirlist = malloc(sizeof(redirlist_t));
    if (redirlist == NULL) {
        perror(RED "Something went wrong when using malloc on redirlist_alloc");
        exit(1);
    }
    redirlist->to_exec = to_exec;
    redirlist->next = NULL;
    redirlist->redir_type = redir_type;
    return redirlist;
}

void redirlist_print(redirlist_t* redirlist) {
    if(redirlist == NULL) { 
        fflush(stdout);
        write(STDOUT_FILENO, "NULL", 5); 
    } else {
        printf(" %s %c ", redirlist->to_exec, redirlist->redir_type);
        redirlist_print(redirlist->next);
    }
}

void redirlist_free(redirlist_t* list) {
    if(list == NULL) return;
    redirlist_free(list->next);
    free(list);
}

IMPL_LIST_APPEND(redirlist_append, redirlist_t)

redirlist_t* redirlist_parse(char* command) {
    char* saveptr = NULL;
    redirlist_t* redirlist = NULL;
    redirlist_t** rediriter = &redirlist;

    for(char* str = command;;str=NULL){
        char* to_exec = strtok_r(str, REDIR_CHARS, &saveptr);
        if (to_exec == NULL) break;

        redirlist_append(rediriter, redirlist_alloc(to_exec, '|'));
        rediriter = &((*rediriter)->next);
    }
    return redirlist;
}

size_t redir_len(redirlist_t* list){
    if(list == NULL) return 0;
    else return redir_len(list->next) + 1;
}

#define PIPE_READ 0
#define PIPE_WRITE 1

static void splitargs(const char** buffer, size_t buffer_size, char* command) {
    char* saveptr;
    char* str = command;
    size_t i = 0;
    for(; i+1<buffer_size ; str=NULL, i++){
        char* cmd = strtok_r(str, " ", &saveptr);
        if (cmd == NULL) break;
        buffer[i] = cmd;
    }
    buffer[i] = NULL;
}

char* SHELL_CMDS_NAMES[] = {
    "exit",
    "cd"
};

typedef void(*shellcmdfunc)(const char** args);

void shell_cmd_exit(const char** args) {
    const char* str_exitno = args[1] == NULL ? "0" : args[1];
    int exitno = atoi(str_exitno);
    exit(exitno);
}

void shell_cmd_cd(const char** args) {
    const char* path = args[1] == NULL ? getenv("HOME") : args[1];
    if(chdir(path) != 0) {
        perror(RED "cd");
    }
}

shellcmdfunc SHELL_CMD_FUNCS[] = {
    &shell_cmd_exit,
    &shell_cmd_cd
};

#define SHELL_CMD_SIZE sizeof(SHELL_CMDS_NAMES)/sizeof(char*)

void execute_cmd(const char** restrict args) {
    for(size_t i = 0; i < SHELL_CMD_SIZE; i++) {
        if(strncmp(SHELL_CMDS_NAMES[i], args[0], 128) == 0) {
            (*SHELL_CMD_FUNCS[i])(args);
            return;
        }
    }
    if(execvp(args[0], args)) {
        perror("Process image transition failed");
        exit(1);
    }
}

int is_shell_cmd(const char** args) {
    for(size_t i = 0; i < SHELL_CMD_SIZE; i++) {
        if(strncmp(SHELL_CMDS_NAMES[i], args[0], 128) == 0) {
            return i;
        }
    }
    return -1;
}

int redir_exec(redirlist_t* list) {
    size_t list_size = redir_len(list);
    redirlist_t* rediriter = list;

    int pipes[list_size][2];

    for(size_t i = 0; i < list_size; i++) {
        pipe(pipes[i]);
    }

    pid_t pids[list_size];
    for(size_t i = 0; i < list_size; i++, rediriter = rediriter->next){
        pid_t pid;

        size_t buf_size = 8;
        const char* args[8];
        splitargs(args, buf_size, rediriter->to_exec);

        int scmdi;

        if ((scmdi = is_shell_cmd(args)) >= 0) {
            execute_cmd(args);
            continue;
        }

        if ((pid = fork()) < 0) {
            perror(RED "Some error on fork at redir_exec");
            exit(-1);
        }
        if (pid == 0) {
            if(i > 0) {
                dup2(pipes[i-1][PIPE_READ], STDIN_FILENO);
            }
            if(i + 1 < list_size) {
                dup2(pipes[i][PIPE_WRITE], STDOUT_FILENO);
            }

            for(size_t j = 0; j < list_size; j++){
                close(pipes[j][PIPE_READ]);
                close(pipes[j][PIPE_WRITE]);
            }

            execute_cmd(args);
        } else {
            pids[i] = pid;
        }
    }

    for(size_t i = 0; i < list_size; i++) {
        close(pipes[i][PIPE_READ]);
        close(pipes[i][PIPE_WRITE]);
    }

    for(size_t i = 0; i < list_size; i++) {
        waitpid(pids[i], NULL, WUNTRACED);
    }

    wait(NULL);
    return 0;
}
