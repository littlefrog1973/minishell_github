#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *command = "ls"; // The command you want to execute
    char *args[] = {command, "-l", NULL}; // Arguments for the command
    char *env[] = {NULL}; // Environment variables

    // Get the value of the PATH environment variable
    char *path = getenv("PATH");
    if (path == NULL) {
        perror("getenv");
        return 1;
    }

    // Tokenize the PATH variable to extract directories
    char *token = strtok(path, ":");
    while (token != NULL) {
        char executablePath[256]; // Adjust the size as needed
        snprintf(executablePath, sizeof(executablePath), "%s/%s", token, command);

        // Try to execute the command using the current directory token
        if (execve(executablePath, args, env) == -1) {
            // execve failed, try the next directory
//            perror("execve");
        }

        token = strtok(NULL, ":"); // Move to the next token
    }

    // If we reach here, execve failed for all directories
    fprintf(stderr, "Command '%s' not found in PATH.\n", command);

    return 1;
}
