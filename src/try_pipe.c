/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:07:16 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/18 13:19:43 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	int	fd[2];
	//fd[0] : read side;
	//fd[1] : write side;

	if (pipe(fd) == -1)
	{
		printf("An error occured with opening the pipe\n");
		return (1);
	}
	int id = fork();
	if (id == -1)
	{
		printf("An error occured with create child process\n");
		return (2);
	}
	if (id == 0)
	{
		close(fd[0]);	// close read side of pipe in child process
		int	x;
		printf("Input a number: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));	//write to write side of pipe
		close(fd[1]);	// after wrote to write side of pipe close it
	}
	else
	{	wait(NULL);
		close(fd[1]);	// close write side of pipe in parent process
		int	y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Got from child process: %d\n", y);
	}
	return (0);
}
