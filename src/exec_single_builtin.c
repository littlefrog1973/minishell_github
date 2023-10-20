/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <pboonpro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:04:23 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/20 00:07:36 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_single_builtin(char **argv, t_pipe *p_pipe, int *status, char ***env)
{
	int		(*fn_ptr[NUM_BUILTIN + 1])(int, char **, char ***);
	char	*fn_list[NUM_BUILTIN + 1];

	(void) p_pipe;
	if (!argv || !env)
		return ;
	init_fn_ptr(fn_ptr, fn_list);
	if (search_str(fn_list, argv[0]) >= 0)
		*status = fn_ptr[search_str(fn_list, argv[0])]((int) count_str(argv),
				argv, env);
	else
		*status = 1;
	return (free_duo_ptr(argv));
}
