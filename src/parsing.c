/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:37:46 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/30 07:44:53 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_env(char *command, char **env)
{
	size_t	i;
	char	buf[BUFSIZ];
	size_t	j;
	ssize_t	k;
	char	buf2[BUFSIZ];
	int		s_quote;
	int		d_quote;

	ft_memset(buf, 0, BUFSIZ);
	i = 0;
	j = 0;
	s_quote = 0;
	d_quote = 0;
	while (command[i])
	{
		if (command[i] == '\'' && !d_quote)
		{
			if (!s_quote)
				s_quote = 1;
			else
				s_quote = 0;
			i++;
			continue ;
		}
		if (command[i] == '"' && !s_quote)
		{
			if (!d_quote)
				d_quote = 1;
			else
				d_quote = 0;
			i++;
			continue ;
		}
		if (s_quote)
		{
			buf[j] = command[i];
			i++;
			j++;
			continue;
		}
		if (d_quote || !s_quote)
		{
			if (command[i] != '$')
			{
				buf[j] = command[i];
				i++;
				j++;
				continue;
			}
			else if (command[i] == '$' && ft_isdigit(command[i + 1]))
				i += 2;
			else if (command[i] == '$' && ft_isalpha(command[i + 1]))
			{
				k = word_len(&command[i + 1]);
				ft_strlcpy(buf2, &command[i + 1], k + 1);
				ft_strlcat(buf2, "=", k + 2);
				if (search_str(env, buf2) >= 0)
					j += ft_strlcpy(&buf[j], &env[search_str(env, buf2)][ft_strlen(buf2)], ft_strlen(&env[search_str(env, buf2)][ft_strlen(buf2)]) + 1);
				i += k + 1;
			}
		}
	}
	return (ft_strdup(buf));
}

char	**interpret(char **command, char **env)
{
	char	*temp;
	int		i;

	i = -1;
	while (command[++i])
	{
		temp = command[i];
		command[i] = ft_strtrim(command[i], WHITE_SPACE);
		if (!command[i])
			return (free_duo_ptr(command), (char **) NULL);
		free(temp);
		temp = command[i];
		command[i] = put_env(command[i], env);
		if (!command[i])
			return (perror("minishell: parsing"), free_duo_ptr(command),
				free(temp), (char**) NULL);
		free(temp);
	}
	return (command);
}

t_file	*find_infile(char *r_line)
// to find infile name and set to struct infile
{
	int		i;
	char	*temp;
	char	*line_to_free;
	t_file	*infile;

	infile = (t_file *) ft_calloc(1, sizeof(t_file));
	if (!infile || !r_line)
		return (perror("minishell: parsing: infile"), NULL);
	if (r_line[0] == '<' && r_line[1] != '<')
	{
		temp = ft_strtrim(&r_line[1], WHITE_SPACE);
		if (!temp)
			return (perror("minishell: parsing: infile"), free(infile), NULL);
		i = -1;
		while (temp[++i])
		{
			if (ft_isspace(temp[i]))
				break ;
		}
		line_to_free = temp;
		temp = ft_substr(temp, 0, i);
		free(line_to_free);
		if (!temp)
			return (perror("minishell: parsing: infile"), free(infile), NULL);
		if (access(temp, R_OK | F_OK) == 0)
		{
			infile->filename = temp;
			infile->type = INFILE;
		}
		else if (access(temp, R_OK | F_OK) == -1)
		{
			free(infile);
			return (NULL);
		}
		return (infile);
	}
	else if (r_line[0] == '<' && r_line[1] == '<')
	{
		temp = ft_strtrim(&r_line[2], WHITE_SPACE);
		if (!temp)
			return (perror("minishell: parsing: infile"), free(infile), NULL);
		i = -1;
		while (temp[++i])
		{
			if (ft_isspace(temp[i]))
				break ;
		}
		line_to_free = temp;
		temp = ft_substr(temp, 0, i);
		free(line_to_free);
		if (!temp)
			return (perror("minishell: parsing: infile"), free(infile), NULL);
		infile->filename = temp;
		infile->type = HEREDOC;
		return (infile);
	}
	else
		return (free(infile), (t_file *) NULL);
}

t_file	*find_outfile(char *r_line)
// to file outfile name and set to struct outfile
{
	char	*temp;
	t_file	*outfile;

	outfile = (t_file *) ft_calloc(1, sizeof(t_file));
	if (!outfile || !r_line)
		return (perror("minishell: parsing: infile"), NULL);
	temp = ft_strrchr(r_line, '>');
	if (!temp)
		return (free(outfile), NULL);
	if (*(temp + 1))
		while (ft_isspace(*(temp + 1)) && *(temp + 1))
			temp++;
	temp = ft_strdup(++temp);
	if (!temp)
		return (perror("minishell: parsing: outfile"), free(outfile), NULL);
	outfile->filename = temp;
	if (*(ft_strrchr(r_line, '>') - 1) == '>' && !access(temp, F_OK | W_OK))
		outfile->type = APPEND;
	else
		outfile->type = OUTFILE;
	return (outfile);
}

t_readline	*parsing_line(char *read_line, char **env)
{
	t_readline	*p_line;
	char		**temp;
	char		*r_line;

	p_line = init_parse_line();
	if (!p_line)
		return (NULL);
	r_line = trim_line(read_line);
	if (!r_line)
		return (free_t_readline(p_line), NULL);
	temp = ft_split(r_line, '|');
	if (!temp)
		return (free_t_readline(p_line), free(r_line), NULL);
	temp = interpret(temp, env);
	if (!temp)
		return (free_t_readline(p_line), free(r_line), free_duo_ptr(temp),
			NULL);
	p_line->n_pipe = count_pipe(r_line);
	p_line->infile = find_infile(temp[0]);
	p_line->outfile = find_outfile(temp[count_str(temp) - 1]);
	p_line->command = del_in_out(temp, p_line->infile, p_line->outfile);
	p_line->r_line = r_line;
	return (p_line);
}
