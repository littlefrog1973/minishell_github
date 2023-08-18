/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:39:20 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/18 10:42:19 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	char	*read_line;

	(void) argc;
	(void) argv;
	read_line = readline(PROMPT);
//	ft_printf("%s\n", read_line);
	ft_printf("%d\n", ft_atoi(read_line) * 10);
	free(read_line);
	return (0);
}
