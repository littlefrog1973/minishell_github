/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:53:56 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/11 13:53:12 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*put_pipe(char *r_line)
{
	int		d_quote;
	int		s_quote;
	size_t	i;
	char	*rr_line;

	rr_line = ft_strdup(r_line);
	if (!rr_line)
		return (NULL);
	d_quote = 0;
	s_quote = 0;
	i = -1;
	while (rr_line[++i])
	{
		set_ds_quote(&s_quote, &d_quote, rr_line[i]);
		if ((s_quote || d_quote) && rr_line[i] == '|')
			rr_line[i] = '|';
		else
			rr_line[i] = ' ';
	}
	return (rr_line);
}

static size_t	seek_str_with_pipe(char **temp1, char *rr_line)
{
	size_t	k;
	size_t	j;
	size_t	l;

	j = ft_strchr(rr_line, '|') - rr_line;
	rr_line[j] = ' ';
	k = 0;
	l = -1;
	while (k < j)
		k += ft_strlen(temp1[++l]) + 1;
	return (l);
}

static char	*rejoin_str(char **temp1, size_t l)
{
	char	*to_free;
	char	buf[BUFSIZ];

	ft_memset(buf, 0, BUFSIZ);
	to_free = temp1[l];
	ft_strlcpy(buf, temp1[l], ft_strlen(temp1[l]) + 1);
	ft_strlcat(buf, "|", ft_strlen(buf) + 2);
	if (temp1[l + 1])
		ft_strlcat(buf, temp1[l + 1], ft_strlen(buf) + ft_strlen(temp1[l + 1])
			+ 1);
	temp1[l] = ft_strdup(buf);
	if (!temp1[l])
		return (perror("parsing: rejoin_str"), NULL);
	free(to_free);
	return (temp1[l]);
}

int	count_pipe_in_quote(char *r_line)
{
	size_t	n_pipe;
	size_t	i;
	int		d_quote;
	int		s_quote;

	i = -1;
	d_quote = 0;
	s_quote = 0;
	n_pipe = 0;
	while (r_line[++i])
	{
		set_ds_quote(&s_quote, &d_quote, r_line[i]);
		if ((s_quote || d_quote) && r_line[i] == '|')
			n_pipe++;
	}
	return (n_pipe);
}

char	**check_pipe_in_quote(char **temp1, char *r_line)
{
	char	*rr_line;
	size_t	i;
	size_t	l;

	rr_line = put_pipe(r_line);
	if (!rr_line)
		return (perror("parsing"), temp1);
	i = (size_t) count_char(rr_line, '|');
	if (!i)
		return (free(rr_line), temp1);
	while (i > 0)
	{
		l = seek_str_with_pipe(temp1, rr_line);
		temp1[l] = rejoin_str(temp1, l);
		if (!temp1[l])
			return (perror("parsing"), free(rr_line), free_duo_ptr(temp1),
				NULL);
		free_ptr(temp1[l + 1]);
		ft_memmove(&temp1[l + 1], &temp1[l + 2], count_str(&temp1[l + 2])
			* sizeof(char *));
		ft_memset(&temp1[l + 1 + count_str(&temp1[l + 2])], 0, sizeof(char *));
		--i;
	}
	return (free(rr_line), temp1);
}
