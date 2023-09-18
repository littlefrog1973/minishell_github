/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:01:31 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/18 20:28:07 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	cd(int argc, char **argv, char ***env)
{
	char	*pwd;
	char	**new_env;
	char	*old_pwd;

	pwd = &((*env)[search_str(*env, "PWD=")][4]);
	if (argc > 2)
		return(perr("minishell: cd: too many arguments\n"), 1);
	else if (argc == 2)
	{
		if (chdir(argv[1]) == -1)
			return (perror("minishell: cd"), 1);
		else
		{
			old_pwd = ft_calloc(ft_strlen(pwd) + 8, sizeof(char));
			if (!old_pwd)
				return (free_double_pointer(argv), free_double_pointer(*env), 1);
			ft_strlcpy(old_pwd, "OLDPWD=", 8);
			ft_strlcat(old_pwd, pwd, (size_t) (ft_strlen(pwd) + 1 + ft_strlen(old_pwd)));
			new_env = env_dup(*env, old_pwd);
			if (!new_env)
				return (free_double_pointer(argv), free_double_pointer(*env), 1);
			free_double_pointer(*env);
			old_pwd = new_env[search_str(new_env, "PWD=")];
			pwd = ft_calloc(ft_strlen(argv[1]) + 5, sizeof(char));
			if (!pwd)
				return (free_double_pointer(argv), free_double_pointer(new_env), 1);
			ft_strlcpy(pwd, "PWD=", 5);
			ft_strlcat(pwd, argv[1], (size_t) (ft_strlen(argv[1]) + 1 + ft_strlen(pwd)));
			new_env[search_str(new_env, "PWD=")] = pwd;
			free(old_pwd);
			*env = new_env;
			return (0);
		}
	}
	else
	{
		old_pwd = ft_calloc(ft_strlen(pwd) + 8, sizeof(char));
		if (!old_pwd)
			return (free_double_pointer(argv), free_double_pointer(*env), 1);
		ft_strlcpy(old_pwd, "OLDPWD=", 8);
		ft_strlcat(old_pwd, pwd, (size_t) (ft_strlen(pwd) + 1 + ft_strlen(old_pwd)));
		new_env = env_dup(*env, old_pwd);
		if (!new_env)
			return (free_double_pointer(argv), free_double_pointer(*env), 1);
		free_double_pointer(*env);
		old_pwd = new_env[search_str(new_env, "PWD=")];
		pwd = ft_calloc(ft_strlen(&new_env[search_str(new_env, "HOME=")][5]) + 6, sizeof(char));
		if (!pwd)
			return (free_double_pointer(argv), free_double_pointer(new_env), 1);
		ft_strlcpy(pwd, "PWD=", 5);
		ft_strlcat(pwd, &new_env[search_str(new_env, "HOME=")][5], (size_t) (ft_strlen(&new_env[search_str(new_env, "HOME=")][5]) + 1 + ft_strlen(pwd)));
		new_env[search_str(new_env, "PWD=")] = pwd;
		free(old_pwd);
		*env = new_env;
		chdir(&((*env)[search_str(*env, "HOME=")][5]));
		return (0);
	}
	return (1);
}
