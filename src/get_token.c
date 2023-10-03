/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:10:59 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/03 11:08:58 by sdeeyien         ###   ########.fr       */
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
			return (perror("get_token"), NULL);
		pointer += (size_t) (ft_strchr(pointer, ':') - pointer) + 1;
		return (token);
	}
	else if (*pointer)
	{
		token = ft_substr(pointer, 0, ft_strlen(pointer));
		if (!token)
			return (perror("get_token"), NULL);
		pointer += ft_strlen(pointer);
		return (token);
	}
	return (NULL);
}

char	*get_token_file(char *line, char *delimit)
{
	static char	*pointer;
	char		*token;
	ssize_t		i;

	if (line != NULL)
		pointer = line;
	if (pointer == NULL)
		return (NULL);
	if (ft_strchr(pointer, delimit[0]))
	{
		pointer = ft_strchr(pointer, delimit[0]) + 1;
		if (*pointer != delimit[0])
		{
			while (ft_isspace(*pointer) && *pointer)
				pointer++;
			i = -1;
			while (!ft_isspace(pointer[++i]) && *pointer);
//				i++;
		}
		else
		{
			pointer++;
			while (ft_isspace(*pointer) && *pointer)
				pointer++;
			i = -1;
			while (!ft_isspace(pointer[++i]) && *pointer);
		}
		token = ft_substr(pointer, 0, i);
		if (!token)
			return(perror("get_token"), NULL);
		pointer = ft_strchr(pointer, delimit[0]);
		return (token);
	}
	else
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
