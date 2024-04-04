#ifndef __REDIR__
#define __REDIR__
#include <stddef.h>

typedef enum redirections_enum {
    PIPE = '|',
    NONE = '0'
}redir_enum;

/*
* Doesn't OWN `to_exec`, user is responsible for FREEING
*/
typedef struct redirection_list {
    redir_enum redir_type;
    char* to_exec;
    struct redirection_list* next;
} redirlist_t;

redirlist_t* redirlist_parse(char* command);
void redirlist_print(redirlist_t* redirlist);
void redirlist_free(redirlist_t* list);
int redir_exec(redirlist_t* list);
size_t redir_len(redirlist_t* list);

#endif
