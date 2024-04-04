#include "command.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void cmdlist_print(commandlist_t* cmdlist) {
    if(cmdlist == NULL) fwrite("NULL", sizeof(char), 5, stdout);
    else {
        printf(" %s ->", cmdlist->command_str);
        cmdlist_print(cmdlist->next);
    }

}

commandlist_t* parse_command(char* command_str) {
    char* saveptr = NULL;
    commandlist_t* cmdlist = allocate_cmdlist(NULL);
    commandlist_t* cmditer = cmdlist;
    for(char* str = command_str;;str=NULL){
        char* cmd = strtok_r(str, ";", &saveptr);
        if (cmd == NULL) break;
        cmditer->next = allocate_cmdlist(cmd);
        cmditer = cmditer->next;
    }
    printf("%p", cmdlist);
    cmdlist_print(cmdlist);
    return cmdlist;
}

commandlist_t* allocate_cmdlist(char* command_str) {
    commandlist_t* cmdlist = malloc(sizeof(commandlist_t));
    cmdlist->command_str = command_str;
    cmdlist->next = NULL;
    return cmdlist;
}

void free_cmdlist(commandlist_t* cmdlist) {
    if(cmdlist == NULL) return;
    free_cmdlist(cmdlist->next);
    //free(cmdlist->command_str);
    free(cmdlist);
}

