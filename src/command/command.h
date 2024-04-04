#ifndef __COMMAND_LIBRARY
#define __COMMAND_LIBRARY

/*
* Doesn't OWN `command_str`, user is responsible for FREEING
*/
typedef struct command_list {
    struct command_list* next;
    char* command_str;
}commandlist_t;

commandlist_t* parse_command(char* command_str);
commandlist_t* allocate_cmdlist(char* command_str);
void free_cmdlist(commandlist_t* cmdlist);

#endif
