#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * display_prompt - function to print display prompt
 *
 * return: void
 */

void display_prompt (){
	printf("$ ");
}

/**
 * execute_command - function to execute command entered by user
 * @command - entered by user 
 * return : void
 */

void execute_command (char *command) {
        pid_t child_pid;
        int status;

        child_pid = fork();

        if (child_pid == 0){
               
                execlp(command,command,(char *)NULL);
               
                perror("execlp status");
                exit(EXIT_FAILURE);
		        }
       else if (child_pid == -1){
              perror("fork failed");
       }
        else{

                waitpid(child_pid, &status, 0);
        }
}

/**
 * main - main function entry of the file execution
 * return: void
 */

int main(){
        char *command=NULL;
        size_t bufsize=0;
        ssize_t characters;

        while(1)
        {
             display_prompt();

           
            characters = getline(&command, &bufsize, stdin);

            
            if (characters == EOF)
            {
                    printf("\n");
                    break;
            }
	    if (command [characters - 1] == '\n')
            {
                  command[characters - 1] = ('\0');
            }
          
            execute_command(command);
        }

        free(command);

        return 0;
        }
