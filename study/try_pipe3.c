/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_pipe3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:55:53 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/24 14:26:49 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int	fd[3][2];
	int	i;
	int	x;

	for (i = 0; i < 3; i++)
	{
		if(pipe(fd[i]) < 0)
			return 1;
	}
	int	pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		//child#1 process
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		int	x = 0;
		if (read(fd[0][0], &x, sizeof(int)) < 0)
			return 3;
		x += 5;
		printf("in child #1 x = %d\n", x);
		if (write(fd[1][1], &x, sizeof(int)) < 0)
			return 4;
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return 5;
	if (pid2 == 0)
	{
		//child#2 process
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int x = 0;
		if (read(fd[1][0], &x, sizeof(int)) < 0)
			return 6;
		x += 5;
		printf("in child #2 x = %d\n", x);
		if (write(fd[2][1], &x, sizeof(int)) < 0)
			return 7;
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	//parent process
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	x = 10;
	if (write(fd[0][1], &x, sizeof(int)) < 0)
		return 8;
	if (read(fd[2][0], &x, sizeof(int)) < 0)
		return 9;
	printf("#Result is %d\n", x);
	close(fd[0][1]);
	close(fd[2][0]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
