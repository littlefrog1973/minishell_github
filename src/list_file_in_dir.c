/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_file_in_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:43:21 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/31 09:52:14 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void	listFiles(const char *dirname)
{
	DIR	*dir = opendir(dirname);
	if (dir == NULL)
	{
		perror("opendir");
		return;
	}
	printf("Reading files in: %s\n", dirname);
	struct dirent	*entity;
	entity = readdir(dir);
	while (entity != NULL)
	{
		printf("%hhd %s/%s\n", entity->d_type, dirname, entity->d_name);
		if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0)
		{
			char	path[100] = {0};
			strlcat(path, dirname, strlen(dirname) + 1);
			strlcat(path, "/", strlen(path) + 2);
			strlcat(path, entity->d_name, strlen(entity->d_name) + strlen(path) + 1);
			listFiles(path);

		}
		entity = readdir(dir);
	}
	closedir(dir);
}

int	main(int argc, char *argv[])
{
	listFiles(".");
	return 0;
}
