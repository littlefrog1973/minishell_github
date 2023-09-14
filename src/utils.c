/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:31:13 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/14 16:26:05 by sdeeyien         ###   ########.fr       */
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
