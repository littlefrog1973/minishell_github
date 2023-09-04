/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:02:28 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/03 07:54:41 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
//#include <ncurses/termcap.h>
#include <termcap.h>
#include <string.h>

int main() {
    // Initialize termcap database
    char *termtype = getenv("TERM");
    char **buffer = (char **) malloc(4096);
    memset(buffer, 0, 4096);
    if (termtype == NULL) {
        fprintf(stderr, "TERM environment variable not set.\n");
        return 1;
    }

    if (tgetent(NULL, termtype) != 1) {
        fprintf(stderr, "Failed to initialize termcap database.\n");
        return 1;
    }

    // Retrieve terminal capabilities
    int cols = tgetnum("co");
    int lines = tgetnum("li");
    int hasInsert = tgetflag("smir");
    char *clearScreen = tgetstr("cl", buffer);

    if (cols == -1 || lines == -1 || clearScreen == NULL) {
        fprintf(stderr, "Failed to retrieve terminal capabilities.\n");
        return 1;
    }
//    printf("clearScreen=%s", clearScreen);
//    printf("buffer=%s", buffer[0]);
    // Clear the screen
    tputs(clearScreen, 1, putchar);

    // Print information
    printf("Terminal type: %s\n", termtype);
    printf("Columns: %d\n", cols);
    printf("Lines: %d\n", lines);
    printf("Insert mode supported: %s\n", hasInsert ? "Yes" : "No");

    // Move cursor using tgoto
    int x = 0;
    int y = 5;
    char *moveCursor = tgoto(tgetstr("cm", NULL), x, y);
    tputs(moveCursor, 1, putchar);

    // Print a message
    printf("Cursor moved to (%d, %d)\n", x, y);
    free(buffer);
    return 0;
}
