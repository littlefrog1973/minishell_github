/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:21:15 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/25 15:48:05 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(char **argv, char **envp, int i)
{
	int		status;
	int 	fd[2];
	int		pip;
	pid_t	pid;
	char	full_path[PATH_MAX];

	pip = (argv[i] && !ft_strncmp(argv[i], "|", 1));
	if (pip && pipe(fd) == -1)
		return (perror("minishell: exec"), 1);
	pid = fork();
	if (!pid)
	{
		argv[i] = 0;
		if (pip && (close(fd[0]) == -1 || dup2(fd[1], STDOUT_FILENO) == -1 || close(fd[1]) == -1))
			return (perror("minishell: exec"), 1);
		if (get_fullpath(argv[0], full_path, envp))
			execve(full_path, argv, envp);
		return (perr("error: cannot execute"), perr(*argv), perr("\n"), 1);
	}
	waitpid(pid, &status, 0);
	if (pip && (close(fd[1]) == -1 || dup2(fd[0], STDIN_FILENO) == -1 || close(fd[0]) == -1))
		return (perror("minishell: exec"), 1);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}