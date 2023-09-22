/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:39:20 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/22 13:11:06 by sdeeyien         ###   ########.fr       */
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

//	path = getenv("PATH");
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

char	*parse_line(char *read_line)
{
	char	*temp;

	if (!read_line)
		return (NULL);
	temp = ft_strtrim(read_line, WHITE_SPACE);
	if (temp == NULL)
	{
		free (read_line);
		return (NULL);
//		exit (1);
	}
	free (read_line);
	return (temp);
}

int	main(int argc, char *argv[], char *environ[])
{
	char		*read_line;
	char		**argcc;
	pid_t		pid;
	char		full_path[PATH_MAX];
	char		**new_env;

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
		read_line = parse_line(read_line);
		if (!read_line || !ft_strncmp(read_line, "exit", sizeof("exit") - 1))
		{
			if (!read_line)
			{
				printf("exit\n");
				free_duo_ptr(new_env);
				rl_clear_history();
				exit (EXIT_FAILURE);
			}
			free_duo_ptr(new_env);
			free(read_line);
			rl_clear_history();
			exit (EXIT_SUCCESS);
		}
		argcc = ft_split(read_line, ' ');
		if (argcc == NULL)
		{
			free (read_line);
			rl_clear_history();
			exit (EXIT_FAILURE);
		}
		if (!ft_strncmp(read_line, "cd", sizeof("cd") - 1))
		{
			cd((int) count_str(argcc), argcc, &new_env);
			free(read_line);
			free_duo_ptr(argcc);
			continue;
		}
		if (!ft_strncmp(read_line, "export", sizeof("export") - 1))
		{
			export((int) count_str(argcc), argcc, &new_env);
			free(read_line);
			free_duo_ptr(argcc);
			continue;
		}
		if (!ft_strncmp(read_line, "unset", sizeof("unset") - 1))
		{
			unset((int) count_str(argcc), argcc, &new_env);
			free(read_line);
			free_duo_ptr(argcc);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			if (get_fullpath(argcc[0], full_path, new_env))
			{
				if (execve(full_path, argcc, environ) == -1)
					break;
			}
			else
			{
				printf("Executable file does not exist or is not executable.\n");
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(NULL);
		free(read_line);
		free_duo_ptr(argcc);
	}
	if (new_env)
		free_duo_ptr(new_env);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
