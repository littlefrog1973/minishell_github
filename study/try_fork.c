/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:14:17 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/25 11:16:07 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define NUM_PROCESS 3
int	main(void)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < NUM_PROCESS)
	{
		pid = fork();
		if (!pid)
		{
			printf("printed from child\n");
		}
	}
	wait(NULL);
	printf("printed in parent\n");
}
