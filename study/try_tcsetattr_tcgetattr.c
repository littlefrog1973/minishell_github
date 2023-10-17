/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_tcsetattr_tcgetattr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:57:51 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/17 15:51:52 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios originalAttributes, newAttributes;

    // Get the current terminal attributes
    if (tcgetattr(STDIN_FILENO, &originalAttributes) == -1) {
        perror("tcgetattr");
        return 1;
    }

    // Make a copy of the original attributes to modify
    newAttributes = originalAttributes;

    // Disable canonical mode and enable raw mode
    newAttributes.c_lflag &= ~(ICANON | ECHO);

    // Set a minimal input read timeout
    newAttributes.c_cc[VTIME] = 0;
    newAttributes.c_cc[VMIN] = 1;
//  newAttributes.c_cc[VQUIT] = 0;

    // Apply the modified attributes to the terminal
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &newAttributes) == -1) {
        perror("tcsetattr");
        return 1;
    }

    printf("Type characters, press 'q' to quit.\n");

    char c;
    while (1) {
        if (read(STDIN_FILENO, &c, 1) == -1) {
            perror("read");
            return 1;
        }

        if (c == 'q') {
            break;
        }
//        write(STDOUT_FILENO, &c, 1);
        printf("You typed: %c\n", c);
    }

    // Restore the original terminal attributes
    if (tcsetattr(STDIN_FILENO, TCSANOW, &originalAttributes) == -1) {
        perror("tcsetattr");
        return 1;
    }

    return 0;
}
