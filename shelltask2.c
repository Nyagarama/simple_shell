#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10


/**
 * display_prompt - function to display prompt
 * return : void
 */

void display_prompt() {
    printf("$ ");
}

/**
 * execute_command - function to create a child process that executes a command entered by the user
 * @command_line - command entered by a user
 * return: void
 */

void execute_command(char *command_line) {
    pid_t child_pid;
    int status;

    char *args[MAX_ARGS];
    int i = 0;

    char *token = strtok(command_line, " ");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;

    child_pid = fork();

    if (child_pid == 0) {

        execvp(args[0], args);
	 perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (child_pid < 0) {

        perror("simple_shell");
    } else {

        waitpid(child_pid, &status, 0);
    }
}

/**
 * main - entry point of the program
 * return: 0 when the program executes successfully
 */

int main() {
    char *command_line = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    while (1) {
        display_prompt();

        characters = getline(&command_line, &bufsize, stdin);

        if (characters == EOF) {
            printf("\n");
            break;
        }

        if (command_line[characters - 1] == '\n') {
            command_line[characters - 1] = '\0';
        }

	execute_command(command_line);
    }

    free(command_line);

    return 0;
}

