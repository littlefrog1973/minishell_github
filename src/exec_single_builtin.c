/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:04:23 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/11 16:14:36 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_single_builtin(char **argv, char ***env)
{
	int		status;
	int		(*fn_ptr[NUM_BUILTIN + 1])(int, char **, char ***);
	char	*fn_list[NUM_BUILTIN + 1];

	if (!argv || !env)
		return (1);
	init_fn_ptr(fn_ptr, fn_list);
	if (search_str(fn_list, argv[0]) >= 0)
		status = fn_ptr[search_str(fn_list, argv[0])]((int) count_str(argv),
				argv, env);
	else
		status = 1;
	return (free_duo_ptr(argv), status);
}
