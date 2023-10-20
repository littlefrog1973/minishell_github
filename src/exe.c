/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 01:19:09 by pboonpro          #+#    #+#             */
/*   Updated: 2023/10/18 01:19:09 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_have_path(char **env, int *i)
{
	while (env[*i])
	{
		if (ft_strnstr(env[*i], "PATH=", 5))
			return (1);
		(*i)++;
	}
	return (0);
}

void	errorh(char **cmd, int mode, char *str)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(str, 2);
	if (mode == 1)
		free_duo_ptr(cmd);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **env)
{
	char	*path;
	char	**my_path;
	char	*j_path;
	int		i;

	i = 0;
	if (!check_have_path(env, &i))
		errorh(NULL, 0, "Command not found\n");
	my_path = ft_split(env[i] + 5, ':');
	i = 0;
	while (my_path[i])
	{
		j_path = ft_strjoin(my_path[i], "/");
		path = ft_strjoin(j_path, cmd);
		free(j_path);
		if (access(path, F_OK | R_OK) == 0)
		{
			free_duo_ptr(my_path);
			return (path);
		}
		free(path);
		i++;
	}
	free_duo_ptr(my_path);
	return (0);
}

int	check_is_path(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strnstr(cmd[i], "/", ft_strlen(cmd[i])))
			if (access(cmd[i], F_OK | R_OK) == 0)
				return (1);
		i++;
	}
	return (0);
}

void	exe_com(t_exe *a, char ***env)
{
	char	*path;

	if (ft_strncmp(a->cmd[0], "\0", 1) == 0)
		errorh(NULL, 0, "Command not found\n");
	if (check_is_path(a->cmd) == 0)
	{
		path = find_path(a->cmd[0], *env);
		if (!path)
			errorh(a->cmd, 0, "Command not found\n");
	}
	else
		path = ft_substr(a->cmd[0], 0, ft_strlen(a->cmd[0]));
	if (execve(path, a->cmd, *env) != 0)
	{
		free(path);
		errorh(a->cmd, 0, "Can't execve\n");
	}
}

int	is_builtin(char **s)
{
	if (!ft_strncmp(s[0], "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(s[0], "export", ft_strlen("export")))
		return (1);
	else if (!ft_strncmp(s[0], "unset", ft_strlen("unset")))
		return (1);
	else if (!ft_strncmp(s[0], "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(s[0], "env", ft_strlen("env")))
		return (1);
	else if (!ft_strncmp(s[0], "pwd", ft_strlen("pwd")))
		return (1);
	else
		return (0);
}

int	do_in_main(char **n)
{
	if (!ft_strncmp(n[0], "export", ft_strlen("export")) && n[1])
		return (1);
	else if (!ft_strncmp(n[0], "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(n[0], "unset", ft_strlen("unset")))
		return (1);
	else
		return (0);
}

void	close_pipe(t_pipe *p, int i, int size)
{
	if (i == -1)
		return ;
	if (i == 0)
		close(p->pipe_fd[(2 * i) + 1]);
	else if (i + 1 == size)
		close(p->pipe_fd[(2 * i) - 2]);
	else
	{
		close(p->pipe_fd[(2 * i) - 2]);
		close(p->pipe_fd[(2 * i) + 1]);
	}
}

void	ft_dup(t_exe *a, int i)
{
	int	j;

	j = 0;
	if (i != -1)
		j = i;
	dup2(a[j].real_in, STDIN_FILENO);
	dup2(a[j].real_out, STDOUT_FILENO);
}

void	close_child_pipe(t_pipe *p)
{
	int	i;
	int	size;

	i = 0;
	size = p->size * 2;
	while (i < size)
	{
		close(p->pipe_fd[i]);
		i++;
	}
}

int	fork_exe(t_exe *a, t_pipe *p_pipe, char ***env, int i)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		ft_dup(a, i);
		dprintf(2, "before exeve : %d\n", i);
		exe_com(a, env);
		if (i != -1)
			close_child_pipe(p_pipe);
	}
	close_pipe(p_pipe, i, a->size_exe);
	return (pid);
}

void	wait_pid(t_exe *a, int *status)
{
	int	i;
	int	size;

	i = 0;
	size = a->size_exe;
	while (i < size)
	{
		waitpid(a[i].pid, status, WUNTRACED);
		*status = WEXITSTATUS(*status);
		i++;
	}
}

int	fork_single(t_exe *a, t_pipe *p_pipe, int *status, char ***env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		exec_single_builtin(a->cmd, p_pipe, status, env);
		exit(*status);
	}
	return (pid);
}

int	have_command(t_exe *a)
{
	int	i;
	int	size;

	i = 0;
	size = a->size_exe;
	while (i < size)
	{
		if (!a[i].cmd[0])
			return (0);
		i++;
	}
	return (1);
}

void	exe(t_exe *a, t_pipe *p_pipe, int *status, char ***env)
{
	int	i;
	int	size;

	i = 0;
	if (!have_command(a))
		return ;
	size = a->size_exe;
	while (i < size)
	{
		if (size == 1) //single comand builtin
		{
			if (is_builtin(a->cmd))
			{
				if (!do_in_main(a->cmd))
					a[i].pid = fork_single(&a[i], p_pipe, status, env);
				else
				{
					exec_single_builtin(a[i].cmd, p_pipe, status, env);
					return ;
				}
			}
			else
				a[i].pid = fork_exe(&a[i], p_pipe, env, -1);
		}
		else
			a[i].pid = fork_exe(&a[i], p_pipe, env, i);
		i++;
	}
	wait_pid(a, status);
}

void	close_here(t_readline *line)
{
	t_readline	*tmp_line;
	t_file		*tmp_file;

	tmp_line = line;
	while (tmp_line)
	{
		tmp_file = tmp_line->infile;
		while (tmp_file)
		{
			if (tmp_file->type == HEREDOC)
				unlink(tmp_file->filename);
			tmp_file = tmp_file->next;
		}
		tmp_line = tmp_line->next;
	}
}

void	close_all(t_exe *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->size_exe)
	{
		j = 0;
		while (j < a->size_fd_in)
		{
			close(a[i].fd_in[j]);
			j++;
		}
		j = 0;
		while (j < a->size_fd_out)
		{
			close(a[i].fd_out[j]);
			j++;
		}
		i++;
	}
}

void	close_file(t_exe *a, t_readline *file)
{
	close_here(file);
	close_all(a);
}
