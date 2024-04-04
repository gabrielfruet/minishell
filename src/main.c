#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "command/command.h"

void print_prompt(void) {
    const uint BUFFER_SIZE = 64;
    char working_directory[BUFFER_SIZE];

    const char* username = getlogin();
    getcwd(working_directory, BUFFER_SIZE);
    printf("%s at %s -> \n", username, working_directory);
}

/**
 * @brief Read user input and removes leading \n.
 * 
 * @return Returns `NULL` if an error occurs, or `buffer` upon success.
 */
char* read_input(char* buffer, int buffer_size) {
    if(NULL == fgets(buffer, buffer_size, stdin)) {
        return NULL;
    }
    size_t len = strlen(buffer);
    buffer[len-1] = '\0';
    return buffer;
}

int main(){
    print_prompt();
    int buffer_size = 512;
    char user_input[buffer_size];
    if (NULL == read_input(user_input, buffer_size)) {
        puts("Something went wrong");
    }
    //cmdlist_t* cmdlist = cmd_parse(user_input);
    //cmdlist_print(cmdlist);
    //cmdlist_free(cmdlist);
    redirlist_t* redirlist = redirlist_parse(user_input);
    redir_exec(redirlist);
    return 0;
}
