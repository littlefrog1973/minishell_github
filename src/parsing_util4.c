/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:00:19 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/10 08:34:54 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_lst_file(char *cmd, t_file *infile, char arrow)
{
	size_t	i;

	while (1)
	{
		i = ft_strchr(cmd, arrow) - cmd;
		cmd[i] = ' ';
		if (cmd[i + 1] == arrow)
			cmd[i + 1] = ' ';
		ft_memset(ft_strnstr(&cmd[i], infile->filename, ft_strlen(&cmd[i])),
			' ', ft_strlen(infile->filename));
		if (infile->next == NULL)
			break ;
		infile = infile->next;
	}
}

char	*del_in_out2(char *ccmd, t_file *infile, t_file *outfile)
{
	ssize_t	i;
	char	*cmd;
	char	*to_return;

	cmd = ft_strdup(ccmd);
	if (!cmd)
		return (perror("parsing"), NULL);
	if (infile)
		set_lst_file(cmd, infile, '<');
	if (outfile)
		set_lst_file(cmd, outfile, '>');
	i = -1;
	while (cmd[++i])
		if (cmd[i] == '<' || cmd[i] == '>')
			cmd[i] = ' ';
	to_return = ft_strtrim(cmd, " ><");
	if (!to_return)
		return (perror("parsing"), free(cmd), NULL);
	return (free(cmd), to_return);
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

void	lstclear_t_file(t_file **lst, void (*del)(void *))
{
	t_file	*tmp;
	t_file	*to_delete;

	tmp = *lst;
	while (tmp->next != NULL)
	{
		to_delete = tmp;
		del(tmp->filename);
		tmp = to_delete->next;
		free(to_delete);
	}
	del(tmp->filename);
	free(tmp);
	*lst = NULL;
}

void	free_t_file(t_file *p_file)
{
	t_file	*running;
	t_file	*current;

	running = p_file;
	while (running)
	{
		current = running;
		free(current->filename);
		running = current->next;
		free(current);
	}
}
