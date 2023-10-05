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

typedef struct s_exe
{
	int	*fd_in;
	int	*fd_out;
	int	*pipe;
}	t_exe;

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

int	do_here(char *name)
{

}

int	*do_fd_in(t_readline *file)
{
	int		size;
	int		*fd;
	t_file	*temp;
	int		i;

	i = 0;
	temp = file->infile;
	size = ft_filesize(file->infile);
	fd = malloc(sizeof(int) * size);
	if (!fd)
		return (0);
	while (temp)
	{
		if (temp->type == INFILE)
			fd[i] = open(temp->filename, O_RDONLY, 0644);
		else if (temp->type == HEREDOC)
			fd[i] = do_here(temp->filename);
		if (!fd[i])
		{
			free(fd);
			return (-1);
		}
		i++;
		temp = temp->next;
	}
	return (fd);
}

int	*do_fd_out(t_readline *file)
{
	int		*fd;
	t_file	*temp;
	int		i;
	int		*fd;

	i = 0;
	temp = file->outfile;
	size = ft_filesize(file->outfile);
	fd = malloc(sizeof(int) * size);
	if (!fd)
		return (0);
	while (temp)
	{
		if (temp->type == OUTFILE)
			fd[i] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp->type == APPEND)
			fd[i] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (!fd[i])
		{
			free(fd);
			return (-1);
		}
		i++;
		temp = temp->next;
	}
	return (fd);
}

t_exe	*do_fd(t_readline *file)
{
	t_exe	*all_fd;

	all_fd = malloc(sizeof(t_exe));
	if (!all_fd)
		return (NULL);
	all_fd->fd_in = do_fd_in(file);
	all_fd->fd_out = do_fd_out(file);
	if (all_fd->fd_in < 0 || all_fd->fd_out < 0)
	{
		free(all_fd);
		return (NULL);
	}
	return (all_fd);
}
