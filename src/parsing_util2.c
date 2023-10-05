/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:54:19 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/04 14:07:22 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_readline(t_readline *tp_line)
{
	if (!tp_line)
		return ;
	else
	{
		if (tp_line->r_line)
			free(tp_line->r_line);
		if (tp_line->command)
			free(tp_line->command);
		if (tp_line->infile)
			free_t_file(tp_line->infile);
		if (tp_line->outfile)
			free_t_file(tp_line->outfile);
	}
}

char	*del_in_out(char *cmd, t_file *infile, t_file *outfile)
{
	char	*move_pos;

	if (infile)
	{
		move_pos = ft_strnstr(cmd, infile->filename, ft_strlen(cmd));
		move_pos += ft_strlen(infile->filename);
		while (!ft_isalnum(*(move_pos)))
			move_pos++;
		ft_memmove(cmd, move_pos, ft_strlen(move_pos) + 1);
	}
	if (outfile)
	{
		move_pos = ft_strrchr(cmd, '>');
		if (move_pos && *(move_pos - 1) == '>')
			*(move_pos - 1) = '\0';
		else
			*move_pos = '\0';
		move_pos--;
		while (ft_isspace(*(move_pos)))
			move_pos--;
		*(++move_pos) = '\0';
	}
	return (ft_strdup(cmd));
}

void	lstadd_back_r_line(t_readline **lst, t_readline *new)
{
	t_readline	*running;

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

void	lstclear_r_line(t_readline **lst, void (*del)(t_readline *))
{
	t_readline	*tmp;
	t_readline	*to_delete;

	tmp = *lst;
	while (tmp->next != NULL)
	{
		to_delete = tmp;
		del(tmp);
		tmp = to_delete->next;
		free(to_delete);
	}
	del(tmp);
	free(tmp);
	*lst = NULL;
}
