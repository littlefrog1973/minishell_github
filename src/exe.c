/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 01:19:09 by pboonpro          #+#    #+#             */
/*   Updated: 2023/10/18 01:19:09 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **s)
{
	if (!ft_strncmp(s[0], "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(s[0], "export", ft_strlen("export")))
		return (1);
	else if (!ft_strncmp(s[0], "unset", ft_strlen("unset")))
		return (1);
	else if (!ft_strncmp(s[0], "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(s[0], "env", ft_strlen("env")))
		return (1);
	else if (!ft_strncmp(s[0], "pwd", ft_strlen("pwd")))
		return (1);
	else
		return (0);
}

int	do_in_main(char **n)
{
	if (!ft_strncmp(n[0], "export", ft_strlen("export")) && n[1])
		return (1);
	else if (!ft_strncmp(n[0], "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(n[0], "unset", ft_strlen("unset")))
		return (1);
	else
		return (0);
}

void	fork_exe(t_exe *a, t_pipe *p_pipe, int *status, char ***env)
{

}

void	in_main_exe(t_exe *a, t_pipe *p_pipe, int *status, char ***env)
{

}

void	exe(t_exe *a, t_pipe *p_pipe, int *status, char ***env)
{
	int	i;

	while (i < a->size_exe)
	{
		if (a->size_exe > 1) //more then 1 command
			fork_exe(a, p_pipe, status, env);
		else if (a->size_exe == 1) //single comand builtin
		{
			if (is_builtin(a->cmd))
			{
				if (!do_in_main(a->cmd))
					fork_exe(a, p_pipe, status, env);
				else
					in_main_exe(a, p_pipe, status, env);
			}
			else
				fork_exe(a, p_pipe, status, env);
		}
		i++;
	}
	waitpid();
	return ;
}
