/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_getenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:39:17 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/21 17:12:21 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *command = "ls"; // The command you want to execute
    char *args[] = {command, "-l", NULL}; // Arguments for the command

    // Get the value of the PATH environment variable
    char *path = getenv("PATH");
    if (path == NULL) {
        perror("getenv");
        return 1;
    }

    // Set up the environment variables for the new process
//    char *env[] = {NULL}; // Start with an empty environment
    size_t env_size = 1; // Count the NULL terminator

    // Iterate through the existing environment variables and include them
    extern char **environ;
    for (size_t i = 0; environ[i] != NULL; i++) {
        env_size++;
    }
    env_size++; // Account for the additional NULL terminator

    char **new_env = (char **)malloc(env_size * sizeof(char *));
    if (new_env == NULL) {
        perror("malloc");
        return 1;
    }

    for (size_t i = 0; environ[i] != NULL; i++) {
        new_env[i] = environ[i];
    }
    new_env[env_size - 1] = NULL;

    // Tokenize the PATH variable to extract directories
    char *token = strtok(path, ":");
    while (token != NULL) {
        char executablePath[256]; // Adjust the size as needed
        snprintf(executablePath, sizeof(executablePath), "%s/%s", token, command);

        // Try to execute the command using the current directory token
        if (execve(executablePath, args, environ) == -1) {
//        if (execve(executablePath, args, new_env) == -1) {
            // execve failed, try the next directory
//            perror("execve");
        }

        token = strtok(NULL, ":"); // Move to the next token
    }

    // If we reach here, execve failed for all directories
    fprintf(stderr, "Command '%s' not found in PATH.\n", command);

    free(new_env); // Clean up the allocated environment array

    return 1;
}
