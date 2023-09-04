/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_hello_world.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 07:22:34 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/01 07:24:11 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>

int	main(void)
{
	initscr();
	printw("Hello World !!!");
	refresh();
	getch();
	endwin();
	return (0);
}
