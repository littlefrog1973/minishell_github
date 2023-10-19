/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: littlefrog <littlefrog@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:17:08 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/19 23:49:30 by littlefrog       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_ds_quote_4args(int *s_quote, int *d_quote, char cmd, size_t *i)
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

	if (!command[*i])
		return (0);
	j = ft_strlen(buf);
	if (command[*i] != '$')
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

char	*put_env(char *cmd, char **env, int status)
{
	char	buf[BUFSIZ];
	size_t	i;
	size_t	j;
	int		s_quote;
	int		d_quote;

	ft_memset(buf, 0, BUFSIZ);
	init_put_env_var(&i, &j, &s_quote, &d_quote);
	while (cmd[i])
	{
		if ((cmd[i] == '\'' && !d_quote) || (cmd[i] == '"' && !s_quote))
		{
			set_ds_quote_4args(&s_quote, &d_quote, cmd[i], &i);
			continue ;
		}
		if (s_quote)
			dup_buf(buf, cmd, &i, &j);
		else if (d_quote || !s_quote)
		{
			if (cmd[i] == '$' && cmd[i + 1] == '?')
				j += dup_buf_status(buf, j, status, &i);
			j += dup_buf_env2(buf, cmd, &i, env);
		}
	}
	return (ft_strdup(buf));
}
