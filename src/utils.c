/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:31:13 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/09 23:59:12 by sdeeyien         ###   ########.fr       */
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
	while (str[i])
		i++;
	return (i);
}

void	perr(char *s)
{
	while (*s)
		write(2, s++, 1);
}

void	free_duo_ptr(char **argc)
{
	int	i;

	if (!argc)
		return ;
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
	len = (size_t)(ft_strchr(add_line, '=') - add_line);
	while (++i < 20)
		temp[i] = 0;
	ft_strlcpy(temp, add_line, len + 1);
	return (search_str(env, temp));
}
