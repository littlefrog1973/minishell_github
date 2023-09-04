/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_isatty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:15:54 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/30 16:40:12 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	int	fd1, fd2, fd3;

	fd1 = STDIN_FILENO;
	fd2 = STDOUT_FILENO;
	fd3 = open(argv[1], O_RDONLY);
	if (isatty(fd1))
	{
		printf("fd %d is a terminal\n", fd1);
		printf("terminal name = %s\n", ttyname(fd1));
	}
	else
		printf("fd %d is not a terminal\n", fd1);
	if (isatty(fd2))
	{
		printf("fd %d is a terminal\n", fd2);
		printf("terminal name = %s\n", ttyname(fd2));
	}
	else
		printf("fd %d is not a terminal\n", fd2);
	if (isatty(fd3))
		printf("fd %d is a terminal\n", fd3);
	else
		printf("fd %d is not a terminal\n", fd3);
	printf("ttyslot = %d\n", ttyslot());
	close(fd3);
}
