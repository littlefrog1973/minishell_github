/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:10:59 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/22 23:08:37 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(char *line, char *delimit)
{
	static char	*pointer;
	char		*token;

	if (line != NULL)
		pointer = line;
	if (ft_strchr(pointer, delimit[0]))
	{
		token = ft_substr(pointer, 0, (size_t) (ft_strchr(pointer, delimit[0]) - pointer));
		if (!token)
			exit (1);
		pointer += (size_t) (ft_strchr(pointer, ':') - pointer) + 1;
		return (token);
	}
	else if (*pointer)
	{
		token = ft_substr(pointer, 0, ft_strlen(pointer));
		if (!token)
			exit (1);
		pointer += ft_strlen(pointer);
		return (token);
	}
	return (NULL);
}
/*
int	main(void)
{
	char	test[] = "/usr/bin:/home/littlefrog:/var/etc";
	char	*temp;
	int		i;

	temp = get_token(test, ":");
	i = 1;
	while (temp)
	{
		printf("%d-th token = %s\n", i++, temp);
		free(temp);
		temp = get_token(NULL, ":");
	}
	return (0);
}
*/
