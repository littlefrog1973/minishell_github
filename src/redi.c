/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:53:52 by pboonpro          #+#    #+#             */
/*   Updated: 2023/10/03 22:53:52 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exe	*join_exe(t_readline *file)
{
	int			i;
	t_readline	*tmp;
	t_exe		*new;

	i = 0;
	new->size_exe = ft_filesize(file);
	new = malloc(sizeof(t_exe) * new->size_exe);
	if (!new)
		return (NULL);
	tmp = file;
	while (tmp)
	{
		create_exe(&new[i], tmp);
		tmp = tmp->next;
		i++;
	}
	return (new);
}

void	setup_pipe(t_pipe *p, t_exe *a)
{
	int	i;

	i = 0;
	while (i < a->size_exe)
	{
		if (i == 0)
			a->real_out = p->pipe_fd[(2 * i) + 1];
		else if (i + 1 != a->size_exe)
			a->real_in = p->pipe_fd[(2 * i) - 2];
		else
		{
			a->real_out = p->pipe_fd[(2 * i) + 1];
			a->real_in = p->pipe_fd[(2 * i) - 2];
		}
		i++;
	}
}

void	do_all_redi(t_exe *a, t_pipe *p, t_readline *file)
{
	int	i;
	int	j;

	i = 0;
	do_fd_in(a, file);
	do_fd_out(a, file);
	setup_pipe(p, a);
	while (i < a->size_exe)
	{
		if (a->size_fd_in != -1)
			a->real_in = a->fd_in[a->size_fd_in - 1];
		if (a->size_fd_out != -1)
			a->real_out = a->fd_out[a->size_fd_out - 1];
		i++;
	}
}

void	do_pipe(int npipe, t_pipe *a)
{
	int	i;

	i = 0;
	a->size = npipe;
	if (npipe < 1)
	{
		a->pipe_fd = NULL;
		a->size = 0;
		return ;
	}
	a->pipe_fd = malloc(sizeof(int) * npipe);
	while (i < npipe)
	{
		if (pipe(a->pipe_fd + (i * 2)) < 0)
		{
			free(a->pipe_fd);
			return ;
		}
		i += 2;
	}
}

void	main_exe(t_readline *file, int *status, char ***env)
{
	t_exe	*p_exe;
	t_pipe	p_pipe;

	do_pipe(file->n_pipe, &p_pipe);
	p_exe = join_exe(file);
	do_here(p_exe, file);
	do_all_redi(p_exe, &p_pipe, file);
	exe(p_exe, p_pipe, status, env);
	ft_execlear(p_exe, &p_pipe); // close all file if heredoc unlink it
}
