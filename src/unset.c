/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:27:13 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/22 12:24:18 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	search_unset_str(char *str[], char *search)
{
	ssize_t	i;
	char	buff[BUFSIZ];

	i = 0;
	while (str[i])
	{
		set_str(i, str, buff);
		if (!ft_strncmp(buff, search, ft_strlen(search)))
			return (i);
		i++;
	}
	return (-1);
}

int	unset(int argc, char **argv, char ***env)
{
	char	buff[BUFSIZ];
	ssize_t	pos_to_unset;
	size_t	num_move;
	size_t	i;

	if (argc == 1)
		return (0);
	while (--argc > 0)
	{
		ft_strlcpy(buff, argv[argc], ft_strlen(argv[argc]) + 1);
		pos_to_unset = search_unset_str(*env, buff);
		if (pos_to_unset >= 0)
		{
			num_move = count_str(&(*env)[pos_to_unset]);
			free((*env)[pos_to_unset]);
			i = -1;
			while (++i < num_move)
				(*env)[pos_to_unset + i] = (*env)[pos_to_unset + i + 1];
		}
	}
	return (0);
}
