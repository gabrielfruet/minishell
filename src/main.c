#include <stdio.h>
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

int main(){
    print_prompt();
    int buffer_size = 512;
    char user_input[buffer_size];
    if( 0 == fgets(user_input, buffer_size, stdin) ) {
        puts("Something went wrong.");
    }
    commandlist_t* cmdlist = parse_command(user_input);
    free_cmdlist(cmdlist);
    return 0;
}
