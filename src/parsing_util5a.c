/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util5a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:15:15 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/12 14:00:40 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	putnbr_str(char *str, int num, int *i)
{
	if (num >= 10)
		putnbr_str(&str[*i], num / 10, i);
	str[(*i)++] = '0' + (num % 10);
}

size_t	dup_buf_status(char *buf, size_t j, int status, size_t *k)
{
	char	status_str[20];
	int		i;

	*k += 2;
	ft_memset(status_str, 0, 20);
	i = 0;
	putnbr_str(status_str, status, &i);
	ft_memcpy(&buf[j], status_str, ft_strlen(status_str));
	return (ft_strlen(status_str));
}

void	init_put_env_var(size_t *i, size_t *j, int *s_quote, int *d_quote)
{
	*i = 0;
	*j = 0;
	*s_quote = 0;
	*d_quote = 0;
}

void	set_ds_quote(int *s_quote, int *d_quote, char cmd)
{
	if (cmd == '\'' && !(*d_quote))
	{
		if (!(*s_quote))
			*s_quote = 1;
		else
			*s_quote = 0;
	}
	if (cmd == '"' && !(*s_quote))
	{
		if (!(*d_quote))
			*d_quote = 1;
		else
			*d_quote = 0;
	}
}
