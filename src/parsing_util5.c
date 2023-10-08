/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:17:08 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/06 08:20:17 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_ds_quote(int *s_quote, int *d_quote, char cmd, size_t *i)
{
	(*i)++;
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

static void	dup_buf(char *buf, char *cmd, size_t *i, size_t *j)
{
	buf[*j] = cmd[*i];
	(*i)++;
	(*j)++;
}

static size_t	dup_buf_env(char *buf, char *command, size_t *i, char **env)
{
	size_t	j;
	ssize_t	k;
	char	buf2[BUFSIZ];

	j = ft_strlen(buf);
	k = word_len(&command[*i + 1]);
	ft_strlcpy(buf2, &command[*i + 1], k + 1);
	ft_strlcat(buf2, "=", k + 2);
	if (search_str(env, buf2) >= 0)
		j = ft_strlcpy(&buf[j], &env[search_str(env, buf2)]
			[ft_strlen(buf2)], ft_strlen(&env[search_str(env, buf2)]
				[ft_strlen(buf2)]) + 1);
	*i += k + 1;
	return (j);
}

static size_t	dup_buf_env2(char *buf, char *command, size_t *i, char **env)
{
	size_t	j;

	j = ft_strlen(buf);
	if ((command[*i] != '$') || (command[*i] == '$' && command[*i + 1] == '?'))
	{
		dup_buf(buf, command, i, &j);
		return (1);
	}
	else if (command[*i] == '$' && ft_isdigit(command[*i + 1]))
	{
		*i += 2;
		return (0);
	}
	else if (command[*i] == '$' && ft_isalpha(command[*i + 1]))
	{
		j = dup_buf_env(buf, command, i, env);
		return (j);
	}
	return (0);
}

char	*put_env(char *command, char **env)
{
	size_t	i;
	char	buf[BUFSIZ];
	size_t	j;
	int		s_quote;
	int		d_quote;

	ft_memset(buf, 0, BUFSIZ);
	i = 0;
	j = 0;
	s_quote = 0;
	d_quote = 0;
	while (command[i])
	{
		if ((command[i] == '\'' && !d_quote) || (command[i] == '"' && !s_quote))
		{
			set_ds_quote(&s_quote, &d_quote, command[i], &i);
			continue ;
		}
		if (s_quote)
			dup_buf(buf, command, &i, &j);
		else if (d_quote || !s_quote)
			j += dup_buf_env2(buf, command, &i, env);
	}
	return (ft_strdup(buf));
}