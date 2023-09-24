/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:00:49 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/24 22:48:42 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(char **env)
{
	char	buff[BUFSIZ];
	size_t	equal_pos;

	while (*env)
	{
		ft_memset(buff, 0, BUFSIZ);
		if (ft_strchr(*env, '='))
		{
			equal_pos = (size_t)(ft_strchr(*env, '=') - *env);
			ft_strlcpy(buff, *env, equal_pos + 2);
			buff[ft_strlen(buff)] = '"';
			ft_strlcat(buff, &(*env)[equal_pos + 1],
				ft_strlen(&(*env)[equal_pos + 1]) + 3 + equal_pos);
			buff[ft_strlen(buff)] = '"';
		}
		else
			ft_strlcpy(buff, *env, ft_strlen(*env) + 1);
		printf("declare -x %s\n", buff);
		env++;
	}
}

static char	**add_env(char ***env, char *pwd)
{
	char	**new_env;
	ssize_t	i;

	new_env = (char **) ft_calloc(count_str(*env) + 2, sizeof(char *));
	if (!new_env)
		return ((char **) NULL);
	i = count_str(*env);
	while (--i >= 0)
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

static char	**change_env(char ***env, char *pwd)
{
	char	buff[BUFSIZ];
	size_t	change_pos;

	ft_memset(buff, 0, BUFSIZ);
	if (ft_strchr(pwd, '='))
		ft_strlcpy(buff, pwd, (size_t)(ft_strchr(pwd, '=') - pwd + 1));
	else
		ft_strlcpy(buff, pwd, ft_strlen(pwd) + 1);
	change_pos = search_str(*env, buff);
	if (ft_strchr(pwd, '='))
	{
		free((*env)[change_pos]);
		(*env)[change_pos] = ft_strdup(pwd);
		if ((*env)[change_pos] == NULL)
			return ((char **) NULL);
	}
	return (*env);
}

void	set_str(int arc, char *arv[], char *str)
{
	if (ft_strchr(arv[arc], '='))
		ft_strlcpy(str, arv[arc], ft_strchr(arv[arc], '=') - arv[arc] + 1);
	else
		ft_strlcpy(str, arv[arc], ft_strlen(arv[arc]) + 1);
}

int	export(int arc, char **arv, char ***env)
{
	char	**new_env;
	char	str[BUFSIZ];

	if (arc == 1)
		return (print_env((*env)), 0);
	while (--arc > 0)
	{
		set_str(arc, arv, str);
		if (search_str(*env, str) >= 0)
		{
			if (!change_env(env, arv[arc]))
				return (free_duo_ptr(arv), free_duo_ptr(*env), 1);
		}
		else
		{
			new_env = *env;
			new_env = add_env(&new_env, arv[arc]);
			if (!new_env)
				return (free_duo_ptr(arv), free_duo_ptr(*env), 1);
			free_duo_ptr(*env);
			*env = new_env;
			continue ;
		}
	}
	return (0);
}
