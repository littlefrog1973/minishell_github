/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:39:20 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/17 17:08:25 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_promt(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	do_nothing(int signum)
{
	if (signum == SIGQUIT)
	{}
}

int	get_fullpath(const char *line, char *full_path, char **env)
{
	char	*path;
	char	*temp;

	if (search_str(env, "PATH") >= 0)
		path = &env[search_str(env, "PATH=")][sizeof("PATH=") - 1];
	else
		return (0);
	temp = get_token(path, ":");
	while (temp)
	{
		ft_memset(full_path, 0, PATH_MAX);
		ft_strlcpy(full_path, temp, ft_strlen(temp) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, line, ft_strlen(full_path) + ft_strlen(line) + 1);
		if (access(full_path, X_OK) == 0)
			return (1);
		free(temp);
		temp = get_token(NULL, ":");
	}
	return (0);
}

void	void_arg(int *argc, char **argv)
{
	(void) argc;
	(void) argv;
}

int	main(int argc, char *argv[], char *environ[])
{
	char		*read_line;
	char		**new_env;
	int			status;
	t_readline	*p_line;

	status = 1234;
	void_arg(&argc, argv);
	set_terminal();
	signal(SIGINT, return_promt);
	signal(SIGQUIT, do_nothing);
	new_env = env_dup(environ, NULL);
	if (!new_env)
		return (perror("minishell:"), 1);
	while (1)
	{
		read_line = readline(PROMPT);
		if (!read_line)
		{
			printf("exit\n");
			exit (0);
		}
		add_history(read_line);
		p_line = parsing_line(read_line, new_env, status);
		if (!p_line)
		{
			free_ptr(read_line);
			continue ;
		}
		if (!read_line || !ft_strncmp(read_line, "exit", sizeof("exit") - 1))
		{
			if (!read_line)
			{
				printf("exit\n");
				free_duo_ptr(new_env);
				lstclear_r_line(&p_line, free_t_readline);
				rl_clear_history();
				exit (EXIT_FAILURE);
			}
			free_duo_ptr(new_env);
			free(read_line);
			lstclear_r_line(&p_line, free_t_readline);
			rl_clear_history();
			exit (EXIT_SUCCESS);
		}
		else if (!p_line->n_pipe)
			status = exec_single_builtin(ft_split(p_line->command, ' '), &new_env);
		free(read_line);
		lstclear_r_line(&p_line, free_t_readline);
	}
	return (status);
}
