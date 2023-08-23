#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *path = "/user/bin/ls";  // Absolute path to the executable

    // Check if the executable file exists and has execute permission
    if (access(path, X_OK) == 0) {
        char *args[] = {"ls", "-l", NULL};  // Command-line arguments

        // Launch the executable using execve
        execve(path, args, NULL);

        // If execve returns, an error occurred
        perror("execve");
        return 1;
    } else {
        printf("Executable file does not exist or is not executable.\n");
        return 1;
    }
}
