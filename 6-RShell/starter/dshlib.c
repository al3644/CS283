#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"

/**** 
 **** FOR REMOTE SHELL USE YOUR SOLUTION FROM SHELL PART 3 HERE
 **** THE MAIN FUNCTION CALLS THIS ONE AS ITS ENTRY POINT TO
 **** EXECUTE THE SHELL LOCALLY
 ****
 */

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */
int build_cmd_buff(char *cmd_buff, cmd_buff_t *cmd){

    //check
    if (cmd_buff == NULL){
            return WARN_NO_CMDS;
    }

    //allocate memory and check
    char *buffer = malloc(strlen(cmd_buff) + 1);
    if (buffer == NULL){
            return ERR_MEMORY;
    }

    strcpy(buffer, cmd_buff);

    //initalizes and stores buffer
    cmd->argc = 0;
    cmd->_cmd_buffer = buffer;
    char *tk = buffer;
    bool in_quotes = false;

    while (*tk){
            while (*tk == ' ' && in_quotes == false){
                    tk++;
            }

            if (*tk == '\0'){
                    break;
            }

            //checks for quotes
            if (*tk == '"'){
                    in_quotes = true;
                    tk++;
            }

            cmd->argv[cmd->argc++] = tk;

            while (*tk && (*tk != ' ' || in_quotes == true)){
                    if (*tk == '"'){
                            *tk = '\0';
                            in_quotes = false;
                    }
                    tk++;
            }

            if (*tk){
                    *tk = '\0';
                    tk++;
            }

            if (cmd->argc >= CMD_ARGV_MAX - 1){
                    free(buffer);
                    return ERR_CMD_OR_ARGS_TOO_BIG;
                    }
    }

    cmd->argv[cmd->argc] = NULL;
    return OK;
}

int build_cmd_list(char *cmd_line, command_list_t *clist){
    //initialize
    clist->num = 0;

    //check beginning
    if (cmd_line == NULL || strlen(cmd_line) == 0) {
            return WARN_NO_CMDS;
    }

    char *command = cmd_line;

    //loop and check
    while (command != NULL && *command != '\0') {
            while (*command == ' '){
                    command++;
                    if (clist->num >= CMD_MAX) {
                            return ERR_TOO_MANY_COMMANDS;
                    }
            }

    //find next pipe
    char *pipe = strchr(command, '|');
    if (pipe != NULL) {
        *pipe = '\0';
    }

    //for trailing spaces
    char *space_end = command + strlen(command) - 1;
    while (space_end > command && isspace((unsigned char)*space_end)){
            space_end--;
    }
    *(space_end + 1) = '\0';

    //check if empty
    if (strlen(command) == 0) {
        if (pipe != NULL) {
            command = pipe + 1;
            continue;
        }
        else {
            break;
        }
}

if (build_cmd_buff(command, &clist->commands[clist->num]) != OK) {
    return ERR_MEMORY;
}

clist->num++;
    if (pipe != NULL) {
        command = pipe + 1;
    } else {
        break;
    }
}

return (clist->num > 0) ? OK : WARN_NO_CMDS;
}

//maps built in commands
Built_In_Cmds match_command(const char *input){

if (strcmp(input, "cd") == 0){
    return BI_CMD_CD;
}

if (strcmp(input, EXIT_CMD) == 0){
    return BI_CMD_EXIT;
}
return BI_NOT_BI;
}

Built_In_Cmds exec_built_in_cmd(cmd_buff_t *cmd){

if (strcmp(cmd->argv[0], EXIT_CMD) == 0) {
            exit(0);
    }

    if (strcmp(cmd->argv[0], "cd") == 0) {
            if (cmd->argc == 1) {
            return BI_EXECUTED;
    }

    if (cmd->argc == 2) {
            if (chdir(cmd->argv[1]) != 0) {
            perror("cd");
    }
    return BI_EXECUTED;
    }
else{
    fprintf(stderr, "cd: too many arguments\n");
}
}
return BI_NOT_BI;
}

int exec_local_cmd_loop()
{
    char cmd_buff[SH_CMD_MAX];
    command_list_t clist;

    while(1){
        printf("%s", SH_PROMPT);
        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
            printf("\n");
            break;
     }
     cmd_buff[strcspn(cmd_buff,"\n")] = '\0';

    if (strlen(cmd_buff) == 0) {
        printf(CMD_WARN_NO_CMD);
        continue;
    }

    //error checking based on dshlib.h file 
int rc = build_cmd_list(cmd_buff, &clist);
    if (rc != OK) {
        if (rc == ERR_TOO_MANY_COMMANDS) {
            printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
        } else if (rc == WARN_NO_CMDS) {
            printf(CMD_WARN_NO_CMD);
        } else if (rc == ERR_CMD_OR_ARGS_TOO_BIG) {
            printf("error: command or arguments too big\n");
        } else if (rc == ERR_MEMORY) {
            printf("error: memory allocation error\n");
        } else if (rc == ERR_EXEC_CMD) {
            printf("error: failed to execute command\n");
        } else {
            printf("unknown error occurred\n");
        }
        continue;
    }

//checks if built-in and frees memory 
Built_In_Cmds built_in_cmd = match_command(clist.commands[0].argv[0]);
if (built_in_cmd != BI_NOT_BI) {
        exec_built_in_cmd(&clist.commands[0]);
        for (int i = 0; i < clist.num; i++) {
            free(clist.commands[i]._cmd_buffer);
        }
        continue; 
}

    // execute commands with pipes
    int num_cmds = clist.num;
    int pipes[num_cmds - 1][2];
    pid_t pids[num_cmds];

    //make pipes
    for (int i = 0; i < num_cmds - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    //fork and execute commands
    for (int i = 0; i < num_cmds; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        //child process
        if (pids[i] == 0) {
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            if (i < num_cmds - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            //close pipe ends
            for (int j = 0; j < num_cmds - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            //handle execvp errors
            if (execvp(clist.commands[i].argv[0], clist.commands[i].argv) == -1) {
                    perror("execvp");
                    exit(EXIT_FAILURE);
            }
        }
    }

    //close parents
    for (int i = 0; i < num_cmds - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    //wait for child processes
    for (int i = 0; i < num_cmds; i++) {
        waitpid(pids[i], NULL, 0);
    }

    //free child processes
    for (int i = 0; i < num_cmds; i++){
            free(clist.commands[i]._cmd_buffer);
    }
}
return OK;
}
