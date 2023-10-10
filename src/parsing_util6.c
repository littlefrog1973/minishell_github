/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:53:56 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/10 15:59:40 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **check_pipe_in_quote(char **temp1, char *r_line)
{
	char	*rr_line;
	int		d_quote;
	int		s_quote;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	char	*to_free;
	char	buf[BUFSIZ];


	(void) temp1;
	rr_line = ft_strdup(r_line);
	if (!rr_line)
		return (NULL);
	d_quote = 0;
	s_quote = 0;
	i = -1;
	while (rr_line[++i])
	{
		if (rr_line[i] == '\'' && !d_quote)
		{
			if (!s_quote)
				s_quote = 1;
			else
				s_quote = 0;
		}
		if (rr_line[i] == '"' && !s_quote)
		{
			if (!d_quote)
				d_quote = 1;
			else
				d_quote = 0;
		}
		if ((s_quote || d_quote) && rr_line[i] == '|')
			rr_line[i] = '|';
		else
			rr_line[i] = ' ';
	}
	i = count_char(rr_line, '|');
	while (i > 0)
	{
		ft_memset(buf, 0, BUFSIZ);
		j = ft_strchr(rr_line, '|') - rr_line;
		rr_line[j] = ' ';
		k = 0;
		l = -1;
		while (k < j)
		{
			k += ft_strlen(temp1[++l]) + 1;
		}
		to_free = temp1[l];
		ft_strlcpy(buf, temp1[l], ft_strlen(temp1[l]) + 1);
		ft_strlcat(buf, "|", ft_strlen(buf) + 2);
		ft_strlcat(buf, temp1[l + 1], ft_strlen(buf) + ft_strlen(temp1[l + 1]) + 1);
		temp1[l] = ft_strdup(buf);
		free(temp1[l + 1]);
		free(to_free);
		ft_memmove(&temp1[l + 1], &temp1[l + 2], count_str(&temp1[l + 2]) * sizeof(char *));
		ft_memset(&temp1[l + 1 + count_str(&temp1[l + 2])], 0, sizeof(char *));
		--i;
	}
	return (temp1);
}
