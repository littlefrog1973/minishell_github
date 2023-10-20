/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:23:41 by pboonpro          #+#    #+#             */
/*   Updated: 2023/10/17 23:23:41 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fd_in(char *name)
{
	int	fd;

	if (!access(name, F_OK | R_OK))
	{
		fd = open(name, O_RDONLY, 0644);
		return (fd);
	}
	else
	{
		if (access(name, F_OK))
			error_file(name, 3);
		else if (access(name, W_OK))
			error_file(name, 4);
		return (0);
	}
}

int	check_fd_out(char *name)
{
	int	fd;

	if (access(name, F_OK) || !access(name, W_OK))
	{
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (fd);
	}
	else
	{
		error_file(name, 4);
		return (0);
	}
}

int	check_fd_app(char *name)
{
	int	fd;

	if (access(name, F_OK) || !access(name, W_OK))
	{
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (fd);
	}
	else
	{
		error_file(name, 4);
		return (0);
	}
}

int	open_here(char *name)
{
	int		fd;
	char	*buff;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		buff = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(name, buff, ft_strlen(name)) \
				&& (ft_strlen(buff) - 1) == ft_strlen(name))
		{
			free(buff);
			break ;
		}
		write(fd, buff, ft_strlen(buff));
		free(buff);
	}
	return (fd);
}

void	error_file(char *s, int mode)
{
	ft_putstr_fd("minishell: ", 2);
	write(2, s, ft_strlen(s));
	if (mode == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (mode == 2)
		ft_putstr_fd(": too many arguments\n", 2);
	else if (mode == 3)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (mode == 4)
		ft_putstr_fd(": Permission denied\n", 2);
}
