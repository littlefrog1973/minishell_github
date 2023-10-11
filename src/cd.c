/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:01:31 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/08 22:41:12 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
