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
	int				size_fd_in;
	int				*fd_out;
	int				size_fd_out;
	int				real_in;
	int				real_out;
	int				size_exe;
	char			**cmd;
}	t_exe;

typedef struct s_pipe
{
	int	*pipe_fd;
	int	size;
}	t_pipe;

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

int	open_here(char *name, t_readline *file)
{
	int		fd;
	char	*buff;
	int		count;

	i = 0;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		buff = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(name, buff, ft_strlen(name)) \
				&& (ft_strlen(buff) - 1) == ft_strlen(name))
		{
			free(buff);
			break ;
		}
		write(fd, buff, ft_strlen(buff));
		free(buff);
	}
	return (fd);
}

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
				a->fd_in[i] = open_here(tmp_file->filename, line);
			i++;
			tmp_file->next;
		}
		tmp_line = tmp_line->next;
	}
}

int	check_fd_in(char *name)
{
	int	fd;

	if (!access(name, F_OK | R_OK))
	{
		fd = open(temp->filename, O_RDONLY, 0644);
		return (fd);
	}
	else
	{
		if (access(name, F_OK))
			// error
		else if (access(name, W_OK))
			// error
	}
}

int	*do_fd_in(t_exe *a, t_readline *file)
{
	t_file	*temp;
	int		i;

	i = 0;
	temp = file->infile;
	while (temp)
	{
		if (temp->type == INFILE)
			a->fd_in[i] = check_fd_in(temp->filename);
		if (!fd[i])
			return (0);
		i++;
		temp = temp->next;
	}
	return (fd);
}

int	check_fd_out(char *name)
{
	int	fd;

	if (access(name, F_OK) || !access(name, W_OK))
	{
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (fd);
	}
	else
	{
		//error statement
	}
}

int	check_fd_app(char *name)
{
	int	fd;

	if (access(name, F_OK) || !access(name, W_OK))
	{
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (fd);
	}
	else
	{
		//error statement
	}
}

int	*do_fd_out(t_exe *a, t_readline *file)
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
		if (!fd[i])
			return (0);
		i++;
		temp = temp->next;
	}
	return (1);
}

void	ft_execlear(t_exe *new, t_pipe *p)
{
	if (new->fd_in)
		free(new->fd_in);
	if (new->fd_out)
		free(new->fd_out);
	if (new->cmd)
		free_duo_ptr(new->cmd);
	if (new)
		free(new);
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
	if (size == 0);
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

t_exe	*join_exe(t_readline *file)
{
	int			i;
	t_readline	*tmp;
	t_exe		*new;

	i = 0;
	new->size_exe = ft_filesize(file);
	new = malloc(sizeof(t_exe) * (new->size_exe + 1));
	if (!new)
		return (NULL);
	tmp = file;
	while (tmp)
	{
		create_exe(&new[i],tmp);
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
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

void	do_all_redi(t_exe *a, t_pipe *p)
{
	int	i;
	int	j;

	i = 0;
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
	t_exe	*p_exe;
	t_pipe	p_pipe;

	do_pipe(file->n_pipe, &p_pipe);
	p_exe = join_exe(file);
	do_here(p_exe, file);
	do_all_redi(p_exe, p_pipe);
	exe();
	ft_execlear(p_exe, p_pipe);
}
