/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:11:25 by pboonpro          #+#    #+#             */
/*   Updated: 2023/09/16 18:11:25 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*name;

	name = NULL;
	name = getcwd(name, 0);
	if (!name)
	{
		perror("error :");
		return (EXIT_FAILURE);
	}
	printf("%s\n", name);
	free(cwd);
	return (EXIT_SUCCESS);
}
