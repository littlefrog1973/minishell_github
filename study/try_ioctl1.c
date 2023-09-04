/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_ioctl1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:48:59 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/31 14:49:33 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    struct winsize ws;

    // Get terminal window size using ioctl
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("ioctl");
        return 1;
    }

    // Print terminal window size information
    printf("Terminal window size:\n");
    printf("  Rows: %d\n", ws.ws_row);
    printf("  Columns: %d\n", ws.ws_col);
    printf("  Horizontal pixels: %d\n", ws.ws_xpixel);
    printf("  Vertical pixels: %d\n", ws.ws_ypixel);

    return 0;
}
