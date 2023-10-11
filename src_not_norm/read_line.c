/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:55:55 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/17 13:57:17 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*readline_wrap(const char *prompt)
{
	return (readline(prompt));
}
/*
int	main(int argc, char *argv[])
{
	char	*line;

	(void) argc;
	line = readline(argv[1]);
	printf("read line = %s\n", line);
	free(line);
	return (0);
}
*/
