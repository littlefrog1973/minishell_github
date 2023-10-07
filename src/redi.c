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
	int				*fd_in;
	int				*fd_out;
	int				real_in;
	int				real_out;
	char			**cmd;
	struct s_exe	*next;
}	t_exe;

typedef struct s_pipe
{
	int	*pipe_fd;
	int	size;
}	t_pipe;

void	ft_execlear(t_exe **lst)
{
	t_exe	*curr;
	t_exe	*after;

	after = *lst;
	while (after)
	{
		curr = after;
		after = curr->next;
		free_duo_ptr(curr->cmd);
		free(curr->fd_in);
		free(curr->fd_out);
		curr = NULL;
	}
	*lst = NULL;
}

t_exe	*ft_exelast(t_exe *lst)
{
	if (!lst)
		return (lst);
	else
	{
		while (lst->next != 0)
			lst = lst->next;
	}
	return (lst);
}

void	ft_exeadd_back(t_exe **lst, t_exe *new)
{
	t_exe	*ptr;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = ft_exelast(*lst);
		ptr->next = new;
		new->next = NULL;
	}
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

int	heredoc_count(t_readline *file)
{
	t_file	*temp;
	int		i;

	i = 0;
	temp = file->infile;
	while (temp)
	{
		if (temp->type == HEREDOC)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	do_here(char *name, t_readline *file)
{
	int		*fd;
	char	*buff;
	int		count;
	int		i;

	i = 0;
	if (!fd)
		return (-1);
	while (i < count)
	{
		fd[i] = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		buff = get_next_line(STDIN_FILENO);
		while (ft_strncmp(name, buff, ft_strlen(name)))
		{

		}
		i++;
	}
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
	int		size;
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

void	*do_fd(t_exe *exe)
{
	t_exe	*all_fd;

	all_fd->fd_in = do_fd_in(exe);
	all_fd->fd_out = do_fd_out(exe);
	if (all_fd->fd_in < 0 || all_fd->fd_out < 0)
	{
		if (all_fd->fd_in)
			free(all_fd->fd_in);
		if (all_fd->fd_out)
			free(all_fd->fd_out);
		free(all_fd);
		return ;
	}
}

t_exe	*create_exe(t_readline *file)
{
	t_exe	*new;
	int		size;

	new = malloc(sizeof(t_exe));
	size = ft_filesize(file->infile);
	new->fd_in = malloc(sizeof(int) * size);
	size = ft_filesize(file->outfile);
	new->fd_out = malloc(sizeof(int) * size);
	new->cmd = ft_split(file->command, " ");
	if (!new || !new->fd_in || !new->fd_out || !new->cmd)
	{
		if (new->cmd)
			free_duo_ptr(new->cmd);
		if (new->fd_in)
			free(new->fd_in);
		if (new->fd_out)
			free(new->fd_out);
		if (new)
			free(new);
		return (NULL);
	}
	return (new);
}

void	join_exe(t_readline *file, t_exe *head)
{
	int			size;
	t_readline	*tmp;
	t_exe		*new;

	tmp = file;
	while (tmp)
	{
		new = create_exe(tmp);
		if (!new)
		{
			ft_execlear(&head);
			return (NULL);
		}
		ft_exeadd_back(&head, new);
		tmp = tmp->next;
	}
}

// void	do_all_redi(t_readline *file)
// {

// }

void	do_pipe(int npipe, t_pipe *a)
{
	int	i;

	i = 0;
	a->size = npipe;
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

void	main_exe(t_readline *file)
{
	t_exe	*head;
	t_pipe	pipe;

	do_pipe(file->n_pipe, &pipe);
	join_exe(file, &head);
	do_heredoc();
	do_all_redi();
	exe();
	free_pipe();
	ft_execlear();
}
