/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:00:49 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/21 16:10:10 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	char	buff[BUFSIZ];
	size_t	equal_pos;

	while (*env)
	{
		ft_memset(buff, 0, BUFSIZ);
		if (ft_strchr(*env, '='))
		{
			equal_pos = (size_t) (ft_strchr(*env, '=') - *env);
			ft_strlcpy(buff, *env, equal_pos + 2);
			buff[ft_strlen(buff)] ='"';
			ft_strlcat(buff, &(*env)[equal_pos + 1], ft_strlen(&(*env)[equal_pos + 1]) + 3 + equal_pos);
			buff[ft_strlen(buff)] = '"';
		}
		else
			ft_strlcpy(buff, *env, ft_strlen(*env) + 1);
		printf("declare -x %s\n", buff);
		env++;
	}
}

char	**add_env(char ***env, char *pwd)
{
	char	**new_env;
	ssize_t	i;

	new_env = (char **) ft_calloc(count_str(*env) + 2, sizeof(char *));
	if (!new_env)
		return ((char **) NULL);
	i = count_str(*env);
	while(--i >= 0)
	{
		new_env[i] = ft_strdup((*env)[i]);
		if (!new_env[i])
			return (free_duo_ptr(new_env), (char **) NULL);
	}
	new_env[count_str(*env)] = ft_strdup(pwd);
	if (!new_env[count_str(*env)])
		return (free_duo_ptr(new_env), (char **) NULL);
	return (new_env);
}

char	**change_env(char ***env, char *pwd)
{
	char	buff[BUFSIZ];
	size_t	change_pos;

	if (ft_strchr(pwd, '=') == NULL)
		return (*env);
	ft_memset(buff, 0, BUFSIZ);
	ft_strlcpy(buff, pwd, (size_t) (ft_strchr(pwd, '=') - pwd + 2));
	change_pos = search_str(*env, buff);
	free((*env)[change_pos]);
	(*env)[change_pos] = ft_strdup(pwd);
	if ((*env)[change_pos] == NULL)
		return ((char **) NULL);
	return (*env);
}

int	export(int argc, char **argv, char ***env)
{
	char	**new_env;
	char	str[BUFSIZ];

	if (argc == 1)
		return (print_env((*env)), 0);
	while(--argc > 0)
	{
		ft_memset(str, 0, BUFSIZ);
		if (ft_strchr(argv[argc], '='))
			ft_strlcpy(str, argv[argc], (ft_strchr(argv[argc], '=') - argv[argc] + 2));
		else
			ft_strlcpy(str, argv[argc], (size_t) (ft_strlen(argv[argc]) + 1));
		if (search_str(*env, str) >= 0)
		{
			if (!change_env(env, argv[argc]))
				return (free_duo_ptr(argv), free_duo_ptr(*env), 1);
		}
		else
		{
			new_env = add_env(env, argv[argc]);
			if (!new_env)
				return (free_duo_ptr(argv), free_duo_ptr(*env), 1);
			free_duo_ptr(*env);
			*env = new_env;
		}
	}
	return (0);
}
/*
char	**update_env(char ***env, char *pwd)
{
	char	buff[BUFSIZ];
	char	**new_env;
	char	*old_pwd;

	ft_bzero(buff, BUFSIZ);
	ft_strlcpy(buff, "OLDPWD=", 8);
	ft_strlcat(buff, pwd, (size_t)(ft_strlen(pwd) + 1 + ft_strlen(buff)));
	new_env = env_dup(*env, buff);
	if (!new_env)
		return ((char **) NULL);
	old_pwd = new_env[search_str(new_env, "PWD=")];
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (free_duo_ptr(new_env), (char **) NULL);
	new_env[search_str(new_env, "PWD=")] = ft_strjoin("PWD=", pwd);
	if (new_env[search_str(new_env, "PWD=")] == NULL)
		return (free_duo_ptr(new_env), free(pwd), (char **) NULL);
	return (free(old_pwd), free(pwd), new_env);
}
*/
/*
int	cd(int argc, char **argv, char ***env)
{
	char	**new_env;

	if (argc > 2)
		return (perr("minishell: cd: too many arguments\n"), 1);
	else if (argc == 2)
	{
		if (argv[1][0] == '-')
		{
			if (search_str(*env, "OLDPWD=") < 0)
				return (printf("-minishell: cd: OLDPWD not set\n"), 1);
			else if (chdir(&(*env)[search_str(*env, "OLDPWD=")][7]) == -1)
				return (perror("minishell: cd"), 1);
		}
		else if (chdir(argv[1]) == -1)
			return (perror("minishell: cd"), 1);
	}
	else if (chdir(&(*env)[search_str(*env, "HOME=")][5]) == -1)
		return (perror("minishell: cd"), 1);
	new_env = update_env(env, &((*env)[search_str(*env, "PWD=")][4]));
	if (!new_env)
		return (free_duo_ptr(argv), free_duo_ptr(*env), 1);
	free_duo_ptr(*env);
	*env = new_env;
	return (0);
}
*/
