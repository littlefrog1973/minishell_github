/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:20:09 by pboonpro          #+#    #+#             */
/*   Updated: 2023/10/17 23:20:09 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exe(t_exe **str, int i)
{
	while (i-- > 0)
		free(str[i]);
	free (str);
}

int	ft_filesize(t_file *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_readlinesize(t_readline *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_execlear(t_exe *new, t_pipe *p)
{
	if (new)
	{
		if (new->fd_in)
			free(new->fd_in);
		if (new->fd_out)
			free(new->fd_out);
		if (new->cmd)
			free_duo_ptr(new->cmd);
		free(new);
	}
	if (p)
	{
		if (p->pipe_fd)
			free(p->pipe_fd);
	}
}

void	create_exe(t_exe *new, t_readline *file)
{
	int	size;

	size = ft_filesize(file->infile);
	new->size_fd_in = size;
	if (size == 0)
		new->fd_in = -1;
	else
		new->fd_in = malloc(sizeof(int) * size);
	size = ft_filesize(file->outfile);
	new->size_fd_out = size;
	if (size == 0)
		new->fd_out = -1;
	else
		new->fd_out = malloc(sizeof(int) * size);
	new->cmd = ft_split(file->command, " ");
	if (!new || !new->cmd || !new->fd_in || !new->fd_out)
	{
		ft_execlear(new, NULL);
		return (NULL);
	}
}
