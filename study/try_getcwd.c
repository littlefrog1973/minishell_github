/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_getcwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:49:56 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/31 13:09:25 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

int	main(int argc, char argv[])
{
	char	short_buf[10];
	char	long_buf[PATH_MAX];

	printf("PATH_MAX = %d\n", PATH_MAX);
	if (getcwd(short_buf, 10) != NULL)
		printf("getcwd with short buf[10] =%s\n", getcwd(short_buf, 10));
	else
		perror("getcwd");
	if (getcwd(long_buf, PATH_MAX) != NULL)
		printf("getcwd with long buf[PATH_MAX] =%s\n", getcwd(long_buf, PATH_MAX));
	else
		perror("getcwd");
	return (0);
}
