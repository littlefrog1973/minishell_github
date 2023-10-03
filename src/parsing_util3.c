/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:01:30 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/03 22:19:34 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_file	*find_infile2(char *r_line)
// to find infile name and put in linked list infile
{
	int		i;
	char	*token;
	char	*line_to_free;
	t_file	*infile;
	t_file	*head;

	head = NULL;
	token = get_token_file(r_line, "<");
	if (!token)
		return (NULL);
	while (token)
	{
		line_to_free = token;
		infile	= (t_file*) ft_calloc(1, sizeof(t_file));
		if (!infile || !r_line)
			return (perror("minishell: parsing: infile"), NULL);
		lstadd_back_t_file(&head, infile);
		if (*token == '<')
		{
			infile->type = HEREDOC;
			token++;
		}
		while (!ft_isalnum(*token))
			token++;
		i = -1;
		while (token[++i])
		{
			if (ft_isspace(token[i]))
				break ;
		}
		token = ft_substr(token, 0, i);
		if (!token)
			return(perror("parsing: infile"), free(line_to_free), free(infile), NULL);
		free(line_to_free);
		infile->filename = token;
		if (infile->type != HEREDOC)
			infile->type = INFILE;
		token = get_token_file(NULL, "<");
		if (token)
			 token += !(infile->type != HEREDOC);
	}
	return (head);
}


t_file	*find_outfile2(char *r_line)
// to find outfile name and put in linked list outfile
{
	int		i;
	char	*token;
	char	*line_to_free;
	t_file	*infile;
	t_file	*head;

	head = NULL;
	token = get_token_file(r_line, ">");
	if (!token)
		return (NULL);
	while (token)
	{
		line_to_free = token;
		infile	= (t_file*) ft_calloc(1, sizeof(t_file));
		if (!infile || !r_line)
			return (perror("minishell: parsing: outfile"), NULL);
		lstadd_back_t_file(&head, infile);
		if (*token == '>')
		{
			infile->type = APPEND;
			token++;
		}
		while (!ft_isalnum(*token))
			token++;
		i = -1;
		while (token[++i])
		{
			if (ft_isspace(token[i]))
				break ;
		}
		token = ft_substr(token, 0, i);
		if (!token)
			return(perror("parsing: outfile"), free(line_to_free), free(infile), NULL);
		free(line_to_free);
		infile->filename = token;
		if (infile->type != APPEND)
			infile->type = OUTFILE;
		token = get_token_file(NULL, ">");
		if (token)
			 token += !(infile->type != APPEND);
	}
	return (head);
}

void	lstadd_back_t_file(t_file **lst, t_file *new)
{
	t_file	*running;

	if (*lst == NULL && new != NULL)
	{
		*lst = new;
	}
	else if (new != NULL)
	{
		running = *lst;
		while (running->next != NULL)
			running = running->next;
		running->next = new;
	}
}
void	lstclear_t_file(t_file **lst, void (*del)(t_file *))
{
	t_file	*tmp;
	t_file	*to_delete;

	tmp = *lst;
	while (tmp->next != NULL)
	{
		del(tmp);
		to_delete = tmp;
		tmp = tmp->next;
		free(to_delete);
	}
	del(tmp);
	free(tmp);
	*lst = NULL;
}

void	free_t_file(t_file *p_file)
{
	if (!p_file)
		return ;
	else
	{
		if (p_file->filename)
			free(p_file->filename);
		free(p_file);
	}
}
