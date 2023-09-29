/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:58:59 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/29 08:50:59 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_to_cmp;

	if (!*needle)
		return ((char *) haystack);
	len_to_cmp = ft_strlen(needle);
	if (!haystack)
		ft_memset(NULL, 1, 100);
	while (*haystack && len > 0)
	{
		if (len < len_to_cmp)
			return (NULL);
		if (!ft_strncmp(haystack, needle, len_to_cmp))
			return ((char *) haystack);
		haystack++;
		len--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char str1[] = "< test.txt cat";
	char *str2 = "test.txt";

	printf("%s\n", strnstr(str1, str2, 14));
	printf("%s\n", ft_strnstr(str1, str2, 14));
	return (0);
}
*/
