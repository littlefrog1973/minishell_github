/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_do.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 00:00:46 by pboonpro          #+#    #+#             */
/*   Updated: 2023/10/18 00:00:46 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_here(t_exe *a, t_readline *line)
{
	int			i;
	t_readline	*tmp_line;
	t_file		*tmp_file;

	tmp_line = line;
	while (tmp_line)
	{
		tmp_file = tmp_line->infile;
		i = 0;
		while (tmp_file)
		{
			if (tmp_file->type == HEREDOC)
				a->fd_in[i] = open_here(tmp_file->filename);
			i++;
			tmp_file = tmp_file->next;
		}
		tmp_line = tmp_line->next;
	}
}

void	do_fd_in(t_exe *a, t_readline *file)
{
	t_file	*temp;
	int		i;

	i = 0;
	temp = file->infile;
	while (temp)
	{
		if (temp->type == INFILE)
			a->fd_in[i] = check_fd_in(temp->filename);
		if (!a->fd_in[i])
			return ;
		i++;
		temp = temp->next;
	}
}

void	do_fd_out(t_exe *a, t_readline *file)
{
	t_file	*temp;
	int		i;

	i = 0;
	temp = file->outfile;
	while (temp)
	{
		if (temp->type == OUTFILE)
			a->fd_out[i] = check_fd_out(temp->filename);
		else if (temp->type == APPEND)
			a->fd_out[i] = check_fd_app(temp->filename);
		if (!a->fd_out[i])
			return ;
		i++;
		temp = temp->next;
	}
}
