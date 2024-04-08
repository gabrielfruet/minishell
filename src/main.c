#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "colors.h"
#include "command/redirection.h"
#include "command/command.h"

void print_prompt(void) {
    const uint BUFFER_SIZE = 64;
    char working_directory[BUFFER_SIZE];

    const char* username = getlogin();
    getcwd(working_directory, BUFFER_SIZE);
    char* home_name = getenv("HOME");
    char* home_start = strstr(working_directory, home_name);
    if (home_start != NULL) {
        size_t home_size = strlen(home_name)*sizeof(char); size_t cwd_size = strlen(working_directory)*sizeof(char);
        memmove(working_directory + 1, working_directory + home_size, BUFFER_SIZE-home_size);
        working_directory[0] = '~';
    }
    time_t current_time = time(NULL);
    struct tm* local_time = localtime(&current_time);

    char hour_minute[6];
    strftime(hour_minute, sizeof(hour_minute)/sizeof(char), "%H:%M", local_time);

    printf(BBLU "%s" WHT " at " YEL "%s\n" CRESET, username, working_directory);
    printf(BHYEL "%s" GRN " → " CRESET, hour_minute);
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
    while(1) {
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
        redirlist_free(redirlist);
    }
    return 0;
}
