#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "dshlib.h"

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

//maps built in commands
Built_In_Cmds match_command(const char *input){

    if (strcmp(input, "cd") == 0){
        return BI_CMD_CD;
    }
    return BI_NOT_BI;
}

//checks commands   
Built_In_Cmds exec_built_in_cmd(cmd_buff_t *cmd){
    Built_In_Cmds bic = match_command(cmd->argv[0]);

    //check cd command 
    if (bic == BI_CMD_CD){
        if (cmd->argc == 1){
		return BI_EXECUTED; 
	}

	if (cmd-> argc == 2){	
        	if (chdir(cmd->argv[1]) != 0)
		perror("cd");
		}
	else{
		fprintf(stderr, "cd: too many arguments\n");
        }
    }
    return bic;
}

int exec_local_cmd_loop()
{
    char *cmd_buff = malloc(ARG_MAX);
    int rc = 0;
    cmd_buff_t cmd;

    //main loop
    while(1){
        printf("%s", SH_PROMPT);
         if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
            printf("\n");
            break;
         }

         //remove the trailing \n from cmd_buff
         cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
  

         //parsing input to cmd_buff_t *cmd_buff
	 rc = build_cmd_buff(cmd_buff, &cmd); 
         if (rc != 0){
            printf(CMD_WARN_NO_CMD); 
            continue; 
         }


        //execute built-in command 
        if (match_command(cmd.argv[0]) != BI_NOT_BI){
           exec_built_in_cmd(&cmd);
           continue;
	}

	//fork process 
        pid_t pid = fork();

        //check 
        if (pid < 0) {
           perror("fork");
           continue;
        }

        //child process 
        if (pid == 0){  
            execvp(cmd.argv[0], cmd.argv);
            perror("execvp");  
            exit(ERR_EXEC_CMD);
        } 

        //parent process 
        else {
            int status;
            waitpid(pid, &status, 0);
        }
   }

        free(cmd_buff);
        return OK;
}
