/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:31:13 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/15 15:07:21 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	search_str(char *str[], char *search)
{
	ssize_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], search, ft_strlen(search)))
			return (i);
		i++;
	}
	return (-1);
}

size_t	count_str(char *str[])
{
	size_t	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	perr(char *s)
{
	while (*s)
		write(2, s++, 1);
}

void	free_double_pointer(char **argc)
{
	int	i;

	i = -1;
	while (argc[++i])
		free(argc[i]);
	if (argc)
		free(argc);
}

ssize_t	new_str(char **env, char *add_line)
{
	char	temp[20];
	int		i;
	size_t	len;

	i = -1;
	len = (size_t) (ft_strchr(add_line, '=') - add_line);
	while(++i < 20)
		temp[i] = 0;
	ft_strlcpy(temp, add_line, len + 1);
	return (search_str(env, temp));
}

char	**env_dup(char **env, char *add_line)
{
	int		i;
	char	**temp;

	i = 0;
	while(env[i] != NULL)
		i++;
	if (add_line)
		i += (new_str(env, add_line) < 0);
	temp = (char **) malloc(++i * sizeof(char *));
	if (temp == NULL)
		return ((char **) NULL);
	else
	{
		i = -1;
		while(env[++i] != NULL)
		{
			temp[i] = ft_calloc((ft_strlen(env[i]) + 1), sizeof(char));
			if (temp[i] == NULL)
			{
				free_double_pointer(temp);
				return ((char **) NULL);
			}
			else
			{
				ft_strlcpy(temp[i], env[i], ft_strlen(env[i]) + 1);
			}
		}
		if (add_line)
		{
			if (new_str(env, add_line) >= 0)
			{
				free(temp[new_str(env, add_line)]);
				temp[new_str(env, add_line)] = ft_strdup(add_line);
			}
			else
				temp[i] = ft_strdup(add_line);
		}
	}
	return (temp);
}
