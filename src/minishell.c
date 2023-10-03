/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:39:20 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/03 20:34:50 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_promt(int signum)
{
	(void) signum;
	if (signum == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_redisplay();
	}
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

	status = 0;
	void_arg(&argc, argv);
	signal(SIGINT, return_promt);
	signal(SIGQUIT, return_promt);
	rl_catch_signals = 0;
	new_env = env_dup(environ, NULL);
	if (!new_env)
		return (perror("minishell:"), 1);
	while (1)
	{
		read_line = readline(PROMPT);
		add_history(read_line);
		p_line = parsing_line(read_line, new_env);
		if (!p_line)
			return(free_duo_ptr(new_env), free(read_line), perror("minishell: main"), 1);
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
		free(read_line);
		lstclear_r_line(&p_line, free_t_readline);
	}
	return (status);
}
