#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
  char *lineptr;
  size_t n;
  int pid;

  pid = fork();
  if (pid == 0)
  {
    while (1) {
      printf("$ ");
      getline(&lineptr, &n, stdin);

      // Parse the command line and execute the command.
      char *command = strtok(lineptr, " ");
      char *args[] = {command};
      execvp(command, args);
    }
  }
  else wait(NULL);
  return 0;
}
