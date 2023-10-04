/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util3_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:28:01 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/04 21:46:54 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_file_name(char *token, t_file *infile, char *redi)
{
	char	*line_to_free;
	char	*line_to_send;
	ssize_t	i;

	line_to_free = token;
	if (*token == redi[0] && redi[0] == '<')
	{
		infile->type = HEREDOC;
		token++;
	}
	if (*token == redi[0] && redi[0] == '>')
	{
		infile->type = APPEND;
		token++;
	}
	while (ft_isspace(*token) && *token)
		token++;
	i = -1;
	while (token[++i])
		if (ft_isspace(token[i]))
			break ;
	line_to_send = ft_substr(token, 0, i);
	return (free(line_to_free), line_to_send);
}

t_file	*find_file(char *r_line, char *redi)
{
	char		*token;
	t_file		*infile;
	t_file		*head;

	head = NULL;
	token = get_token_file(r_line, redi);
	if (!token)
		return (NULL);
	while (token)
	{
		infile = (t_file *) ft_calloc(1, sizeof(t_file));
		if (!infile)
			return (free(token), NULL);
		lstadd_back_t_file(&head, infile);
		token = find_file_name(token, infile, redi);
		if (!token)
			return (perror("parsing: infile"), free(infile), NULL);
		infile->filename = token;
		if (infile->type != HEREDOC && redi[0] == '<')
			infile->type = INFILE;
		if (infile->type != APPEND && redi[0] == '>')
			infile->type = OUTFILE;
		token = get_token_file(NULL, redi);
		if (token && !ft_strncmp("<", redi, 1))
			token += !(infile->type != HEREDOC);
	}
	return (head);
}
