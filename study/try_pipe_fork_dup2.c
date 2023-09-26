#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid_ls, pid_grep, pid_wc;

    pid_ls = fork();

    if (pid_ls == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid_ls == 0) { 					// Child process for ls -l
        close(pipe1[0]);				//close read end of pipe1
        dup2(pipe1[1], STDOUT_FILENO);	//duplicate write end of pipe1 to Standard Out FD
        close(pipe1[1]);				//close write end of pipe1
        close(pipe2[0]); 				// Close unused pipe ends
        close(pipe2[1]);				// Close unused pipe ends

        execlp("ls", "ls", "-l", NULL);

        perror("exec");
        exit(EXIT_FAILURE);
    }

    pid_grep = fork();

    if (pid_grep == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid_grep == 0) { 				// Child process for grep .txt
        close(pipe1[1]);				// close write end of pipe1
        dup2(pipe1[0], STDIN_FILENO);	// duplicate read end of pipe1 to Standard Input FD
        close(pipe1[0]);				// close read end of pipe1
        close(pipe2[0]);				// close read end of pipe2
        dup2(pipe2[1], STDOUT_FILENO);	// duplicate write end of pipe2 to Standard Output FD
        close(pipe2[1]);				// close write end of pipe2

        execlp("grep", "grep", ".txt", NULL);

        perror("exec");
        exit(EXIT_FAILURE);
    }

    pid_wc = fork();

    if (pid_wc == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid_wc == 0) { 					// Child process for wc -l
        close(pipe2[1]);				// close write end of pipe2
        dup2(pipe2[0], STDIN_FILENO);	// duplicate read end of pipe2 to Standard Input FD
        close(pipe2[0]);				// close read end of pipe2
        close(pipe1[0]); 				// Close unused pipe ends
        close(pipe1[1]);				// Close unused pipe ends

        execlp("wc", "wc", "-l", NULL);

        perror("exec");
        exit(EXIT_FAILURE);
    }

    // Close unused pipe ends in the parent process
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for all child processes to finish
    waitpid(pid_ls, NULL, 0);
    waitpid(pid_grep, NULL, 0);
    waitpid(pid_wc, NULL, 0);
	printf("test STDOUT OK\n");

    return 0;
}
