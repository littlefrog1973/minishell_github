/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:33:09 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/05 04:40:55 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_t_file(t_file **file)
{
	(*file) = (t_file *) malloc(sizeof(t_file));
	if (!(*file))
		return (1);
	(*file)->filename = NULL;
	(*file)->type = NONE;
	return (0);
}

t_readline	*init_parse_line(void)
{
	t_readline	*p_line;

	p_line = (t_readline *) malloc(sizeof(t_readline));
	if (!p_line)
		return (NULL);
	p_line->r_line = NULL;
	p_line->command = NULL;
	p_line->n_pipe = 0;
	p_line->infile = NULL;
	p_line->outfile = NULL;
	p_line->next = NULL;
	return (p_line);
}

size_t	word_len(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

char	*trim_line(char *read_line)
// trim white space from front and rear of read_line
{
	char	*temp;

	if (!read_line)
		return (NULL);
	temp = ft_strtrim(read_line, WHITE_SPACE);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

int	count_pipe(char *r_line)
// return number of pipe symbol in readline return (-1) in case of syntax error
{
	int	n_pipe;
	int	i;

	if (!r_line || !(*r_line))
		return (-1);
	n_pipe = 0;
	i = -1;
	while (r_line[++i])
	{
		if (r_line[0] == '|')
			return (-1);
		if (r_line[i] == '|')
			n_pipe++;
	}
	if (r_line[i - 1] == '|')
		return (-1);
	return (n_pipe);
}
