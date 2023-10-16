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

int	echo(int argc, char **argv, char ***env)
{
	int		i;
	int		new_line;

	(void) env;
	new_line = 1;
	i = 1;
	if (argv[i] && ft_strnstr(argv[i], "-n", 2))
	{
		i++;
		new_line = 0;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (i != argc - 1)
			printf(" ");
		i++;
	}
	if (!argv[i] && new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}
