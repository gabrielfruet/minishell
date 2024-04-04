#ifndef __COMMAND__
#define __COMMAND__
#include "redirection.h"

/*
* Doesn't OWN `command_str`, user is responsible for FREEING
*/
typedef struct command_list {
    struct command_list* next;
    //char* command_str;
    redirlist_t* redirlist;
}cmdlist_t;

cmdlist_t* cmd_parse(char* command_str);
void cmdlist_free(cmdlist_t* cmdlist);
void cmdlist_print(cmdlist_t* cmdlist);
//commandlist_t* allocate_cmdlist(char* command_str);

#endif
