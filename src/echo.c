/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:51:07 by pboonpro          #+#    #+#             */
/*   Updated: 2023/09/17 19:51:07 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_count(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	echo_fun(char **argv)
{
	int	i;
	int	new_line;
	int	count;

	new_line = 1;
	i = 1;
	count = argv_count(argv);
	if (str[i] && ft_strnstr(argv[i], "-n", 2))
	{
		i++;
		new_line = 0;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i] && i != count - 1)
			printf(" ");
		i++;
	}
	if (!argv[i] && !new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}
