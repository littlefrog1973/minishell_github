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
	char	*to_free;

	new_line = 1;
	i = 1;
	if (argv[i] && ft_strnstr(argv[i], "-n", 2))
	{
		i++;
		new_line = 0;
	}
	while (argv[i])
	{
		to_free = put_env(argv[i], *env, 0);
		printf("%s", to_free);
		if (i != argc - 1)
			printf(" ");
		free(to_free);
		i++;
	}
	if (!argv[i] && new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}
