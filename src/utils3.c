/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:56:26 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/17 16:59:26 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_terminal(void)
{
	struct termios	old_attr;
	struct termios	new_attr;

	if (tcgetattr(STDIN_FILENO, &old_attr) == -1)
		return (perror("tcgetatr"), 1);
	new_attr = old_attr;
	new_attr.c_cc[VQUIT] = 0;
	new_attr.c_cc[VEOF] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_attr) == -1)
		return (perror("tcsetattr"), 1);
	return (0);
}
