#include "command.h"
#include "redirection.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "list.h"

IMPL_LIST_APPEND(cmdlist_append, cmdlist_t)

static cmdlist_t* cmdlist_alloc(redirlist_t* redirlist) {
    cmdlist_t* cmdlist = malloc(sizeof(cmdlist_t));
    if (cmdlist == NULL) {
        perror("Something went wrong when using malloc on cmdlist_alloc");
        exit(1);
    }
    cmdlist->redirlist = redirlist;
    cmdlist->next = NULL;
    return cmdlist;
}

void cmdlist_print(cmdlist_t* cmdlist) {
    if(cmdlist == NULL) {
        write(STDOUT_FILENO, "NULL", 5);
        fflush(stdout);
    } else {
        write(STDOUT_FILENO, "RedirList[ ", 12);
        redirlist_print(cmdlist->redirlist);
        write(STDOUT_FILENO, "] ", 3);
        cmdlist_print(cmdlist->next);
    }

}


cmdlist_t* cmd_parse(char* prompt) {
    char* saveptr = NULL;
    cmdlist_t* cmdlist = NULL;
    cmdlist_t** cmditer = &cmdlist;

    for(char* str = prompt;;str=NULL){
        char* cmd = strtok_r(str, ";", &saveptr);
        if (cmd == NULL) break;
        
        cmdlist_append(cmditer, cmdlist_alloc(redirlist_parse(cmd)));
        cmditer = &((*cmditer)->next);
    }
    return cmdlist;
}

void cmdlist_free(cmdlist_t* list) {
    if(list == NULL) return;
    redirlist_free(list->redirlist);
    cmdlist_free(list->next);
    free(list);
}

