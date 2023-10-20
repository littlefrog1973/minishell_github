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
	int			size;
	t_readline	*tmp;
	t_exe		*new;

	i = 0;
	size = ft_readlinesize(file);
	new = malloc(sizeof(t_exe) * size);
	if (!new)
		return (NULL);
	new->size_exe = size;
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
	int	size;

	i = 0;
	if (a->size_exe - 1 == 0)
		return ;
	size = a->size_exe;
	while (i < size)
	{
		if (i == 0)
			a[i].real_out = p->pipe_fd[(2 * i) + 1];
		else if (i + 1 == size)
			a[i].real_in = p->pipe_fd[(2 * i) - 2];
		else
		{
			a[i].real_out = p->pipe_fd[(2 * i) + 1];
			a[i].real_in = p->pipe_fd[(2 * i) - 2];
		}
		i++;
	}
}

void	do_all_redi(t_exe *a, t_pipe *p, t_readline *file)
{
	int	i;
	int	size;

	i = 0;
	do_fd_in(a, file);
	do_fd_out(a, file);
	setup_pipe(p, a);
	size = a->size_exe;
	while (i < size)
	{
		if (a[i].size_fd_in != -1 && a[i].fd_in != (int *)(-1))
			a[i].real_in = a[i].fd_in[a[i].size_fd_in - 1];
		if ((a[i].size_fd_out != -1) && (a[i].fd_out != (int *)(-1)))
			a[i].real_out = a[i].fd_out[a[i].size_fd_out - 1];
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
	a->pipe_fd = malloc(sizeof(int) * (npipe * 2));
	while (i < npipe)
	{
		if (pipe(a->pipe_fd + (i * 2)) < 0)
		{
			free(a->pipe_fd);
			return ;
		}
		i++;
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
	exe(p_exe, &p_pipe, status, env);
	close_file(p_exe, file);
	ft_execlear(p_exe, &p_pipe); // close all file if heredoc unlink it
}
