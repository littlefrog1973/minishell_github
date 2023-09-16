/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:01:31 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/16 18:37:58 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(int argc, char **argv, char **env)
{
	if (argc > 2)
		return(perr("minishell: cd: too many arguments\n"), 1);
	else if (argc == 2)
	{
		if (chdir(argv[1]) == -1)
			return (perror("minishell: cd"), 1);
	}
	else
	{
		chdir(&env[search_str(env, "HOME=")][5]);
		return (0);
	}
	return (1);
}
