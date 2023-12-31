/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:15:34 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/12 13:19:41 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**interpret(char **command, char **env, int status)
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
		command[i] = put_env(command[i], env, status);
		if (!command[i])
			return (perror("minishell: parsing"), free_duo_ptr(command),
				free(temp), (char**) NULL);
		free(temp);
	}
	return (command);
}

static char	**set_r_line_temp(char *read_line, char **r_line, char **env,
	int status)
{
	char	**temp1;
	char	**temp2;

	if (!read_line || !(*read_line))
		return ((char **) NULL);
	*r_line = trim_line(read_line);
	if (!(*r_line))
		return (perror("parsing"), (char **) NULL);
	temp1 = ft_split(*r_line, '|');
	temp1 = check_pipe_in_quote(temp1, *r_line);
	if (!temp1)
		return (free(*r_line), (char **) NULL);
	temp2 = interpret(temp1, env, status);
	if (!temp2)
		return (free_duo_ptr(temp1), free(*r_line), (char **) NULL);
	if (temp1 == temp2)
		return (temp2);
	return (free_duo_ptr(temp1), temp2);
}

static t_readline	*set_p_line(t_readline *p_line, char *temp, char *r_line)
// set n_pipe = -1 in case of pipe in the first or in the last of r_line
{
	int	nn_pipe;

	if (count_pipe(r_line) >= 0)
		nn_pipe = count_pipe(r_line) - count_pipe_in_quote(r_line);
	else
		nn_pipe = -1;
	p_line->n_pipe = nn_pipe;
	p_line->infile = find_file(temp, "<");
	p_line->outfile = find_file(temp, ">");
	p_line->r_line = ft_strdup(temp);
	p_line->command = del_in_out2(temp, p_line->infile, p_line->outfile);
	return (p_line);
}

t_readline	*parsing_line(char *read_line, char **env, int status)
{
	t_readline	*p_line;
	char		**temp;
	char		**to_free;
	char		*r_line;
	t_readline	*head;

	if (!(*read_line))
		return (NULL);
	temp = set_r_line_temp(read_line, &r_line, env, status);
	if (!temp || !r_line)
		return (free_ptr(r_line), NULL);
	to_free = temp;
	head = NULL;
	while (*temp)
	{
		p_line = init_parse_line();
		lstadd_back_r_line(&head, p_line);
		p_line = set_p_line(p_line, *temp, r_line);
		if (!p_line || !p_line->command)
			return (free(r_line), free_duo_ptr(to_free), lstclear_r_line(&head,
					free_t_readline), NULL);
		temp++;
	}
	return (free_duo_ptr(to_free), free(r_line), head);
}
