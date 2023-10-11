#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    char*	input = NULL;

    // Initialize readline
//    rl_bind_key('\t', rl_insert);

    // Main loop
    while (1) {
        input = readline("Enter a command: ");

        // Check for Ctrl-D (end-of-file)
        if (input == NULL) {
            printf("\nExiting...\n");
            break;
        }

        // Add input to history
        if (input[0] != '\0') {
            add_history(input);
        }
        // Process the input
        {
			if (strcmp(input, "quit") == 0) {
            	printf("Goodbye!\n");
            free(input);
            break;
        	} else if (strcmp(input, "clear") == 0) {
            	rl_clear_history();
        	} else {
         	   // Move to a new line, replace the line with "Processed: <input>", and redisplay
            	rl_on_new_line();
//				printf("\n");
            	rl_replace_line("Processed: ", 0);
            	rl_redisplay();
        	}
		}
        // Free input
        free(input);
    }

    return 0;
}
