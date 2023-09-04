/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_pipe4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:03:21 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/25 12:38:48 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PROCESS_NUM 10

int	main(int argc, char *argv[])
{
	int	pipes[PROCESS_NUM + 1][2];
	int	i;
	int	pids[PROCESS_NUM];

	for (i = 0; i < PROCESS_NUM + 1; i++)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Error with creating pipe\n");
			return 1;
		}
	}
	for (i = 0; i < PROCESS_NUM; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error with creating process\n");
			return 2;
		}
		if (pids[i] == 0)
		{
			// child #i process
			int	j;
			int	x;

			for (j = 0; j < PROCESS_NUM + 1; j++)
			{
				if (j != i)
					close(pipes[j][0]);	//close all read pipes except own process pipe
				if (j != i + 1)
					close(pipes[j][1]);	//close all write pipes except next process pipe
			}
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
			{
				printf("Error at reading\n");
				return 3;
			}
			printf("Process %d got %d\n", i, x);
			x++;
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
			{
				printf("Error at writing\n");
				return 4;
			}
			printf("Process %d sent %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return 0;
		}
	}
	// Main process
	int	y = 5;
	int	j;
	printf("Main process sent %d\n", y);
	for (j = 0; j < PROCESS_NUM + 1; j++)
	{
		if (j != PROCESS_NUM)
			close(pipes[j][0]);	//close all read pipes except own process pipe
		if (j != 0)
			close(pipes[j][1]);	//close all write pipes except next process pipe
	}
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
	{
		printf("Error at writing\n");
		return 4;
	}
	if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1)
	{
		printf("Error at reading\n");
		return 3;
	}
	close(pipes[0][1]);
	close(pipes[PROCESS_NUM][0]);

	printf("The final result is %d\n", y);

	for (i = 0; i < PROCESS_NUM; i++)
		wait(NULL);
}
