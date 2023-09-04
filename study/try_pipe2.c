/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_pipe2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:57:07 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/24 11:55:08 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	int pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)	// in child process #1 ping
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "133.124.12.1", NULL);
	}
	int	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)	//in child process #2 grep
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
