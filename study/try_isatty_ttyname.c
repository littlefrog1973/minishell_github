/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_isatty_ttyname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:27:00 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/31 14:34:04 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	int	fd1;

	if (isatty(STDIN_FILENO))
		printf("STDIN_FILENO is associated with a terminal device\n");
	if (isatty(STDOUT_FILENO))
		printf("STDOUT_FILENO is associated with a terminal device\n");
	if (isatty(STDERR_FILENO))
		printf("STDERR_FILENO is associated with a terminal device\n");
	fd1 = open("/dev/null", O_WRONLY);
	if (isatty(fd1))
		printf("/dev/null is associated with a terminal device\n");
	else
		printf("/dev/null is not associated with a terminal device\n");
	printf("ttyname = %s\n", ttyname(STDIN_FILENO));
	return (0);
}
