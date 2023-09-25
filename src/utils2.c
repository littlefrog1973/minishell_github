/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:45:00 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/25 14:24:35 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**adding_line(char **env, char **temp, char *add_line, size_t i)
{
	char	*line_to_add;

	if (!add_line)
		return (temp);
	line_to_add = ft_strdup(add_line);
	if (!line_to_add)
	{
		free_duo_ptr(temp);
		return ((char **) NULL);
	}
	else
	{
		if (new_str(env, add_line) >= 0)
		{
			free(temp[new_str(env, add_line)]);
			temp[new_str(env, add_line)] = line_to_add;
		}
		else
		temp[i] = line_to_add;
	}
	return (temp);
}

char	**env_dup(char **env, char *add_line)
{
	size_t	i;
	char	**temp;

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
		temp = adding_line(env, temp, add_line, i);
		if (!temp)
			return (perror("cd"), (char **) NULL);
	}
	return (temp);
}

void	init_fn_ptr(int (*fn_ptr[])(int, char **, char ***), char **list)
{
	fn_ptr[0] = cd;
	fn_ptr[1] = export;
	fn_ptr[2] = unset;
	fn_ptr[3] = NULL;
	list[0] = "cd\0";
	list[1] = "export\0";
	list[2] = "unset\0";
	list[3] = NULL;
}

/*
	ft_ptr[0] = echo;
	ft_ptr[1] = cd;
	ft_ptr[2] = pwd;
	ft_ptr[3] = export;
	ft_ptr[4] = unset;
	ft_ptr[5] = env;
	ft_ptr[6] = exit;
	ft_ptr[7] = NULL;
	list[0] = "echo\0";
	list[1] = "cd\0";
	list[2] = "pwd\0";
	list[3] = "export\0";
	list[4] = "unset\0";
	list[5] = "env\0";
*/
