/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:58:49 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/15 11:41:18 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	s2 = (char *) malloc(len);
	if (!s2)
	{
		return (NULL);
	}
	len = ft_strlcpy(s2, (char *) s1, len);
	return (s2);
}
/*
#include <stdio.h>
int	main(void)
{
	char	str1[] = "";
	char	*str2;

	str2 = ft_strdup(str1);
	printf("str1  = %s\n", str1);
	printf("str2  = %s\n", str2);
	return (0);
}*/
