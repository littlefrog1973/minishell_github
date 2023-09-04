/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_chdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:08:43 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/31 13:17:21 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>

int	main(int argc, char *argv[])
{
	char	buf[PATH_MAX];
	if (chdir(argv[1]) == -1)
	{
		perror("chdir");
		return (1);
	}
	else
		printf("current directory was changed to %s\n", getcwd(buf, PATH_MAX));
	return (0);
}
