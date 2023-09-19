/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:45:00 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/19 23:17:54 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_dup(char **env, char *add_line)
{
	size_t	i;
	char	**temp;
	char	*line_to_add;

	i = count_str(env);
	if (add_line)
		i += (new_str(env, add_line) < 0);
	temp = (char **) ft_calloc(++i, sizeof(char *));
	if (!temp)
		return (perror("cd"), (char **) NULL);
	else
	{
		i = -1;
		while (env[++i] != NULL)
		{
			temp[i] = ft_strdup(env[i]);
			if (temp[i] == NULL)
				return (free_duo_ptr(temp), perror("cd"), (char **) NULL);
		}
		if (add_line)
		{
			line_to_add = ft_strdup(add_line);
			if (!line_to_add)
				return (free_duo_ptr(temp), perror("cd"), (char **) NULL);
			if (new_str(env, add_line) >= 0)
			{
				free(temp[new_str(env, add_line)]);
				temp[new_str(env, add_line)] = line_to_add;
			}
			else
				temp[i] = line_to_add;
		}
	}
	return (temp);
}
