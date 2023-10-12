/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:20:54 by pboonpro          #+#    #+#             */
/*   Updated: 2023/09/16 18:20:54 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(int argc, char **argv, char ***envv)
{
	int	i;

	(void) argc;
	(void) argv;
	if (!(*envv))
		return (EXIT_FAILURE);
	i = 0;
	while ((*envv)[i])
	{
		printf("%s\n", (*envv)[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
