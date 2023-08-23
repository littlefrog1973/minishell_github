#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

void execute_command(char *args[])
{
	pid_t pid = fork();

	if (pid == 0) {
	// Child process
		if (execve(args[0], args, (char **) NULL) == -1) {
			perror("execve");
//		if (execvp(args[0], args) == -1) {
//			perror("execvp");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        perror("fork");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[64]; // Maximum number of arguments
    int status;

    while (1) {
        printf("SimpleShell> ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            // Exit the shell
            break;
        }

        // Tokenize input
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (i > 0) {
            // Handle built-in commands
            if (strcmp(args[0], "cd") == 0) {
                if (i > 1) {
                    if (chdir(args[1]) != 0) {
                        perror("chdir");
                    }
                } else {
                    fprintf(stderr, "cd: Missing argument\n");
                }
            } else {
                // Execute other commands
                execute_command(args);
            }
        }
    }

    return 0;
}
