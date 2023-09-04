/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_getenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:38:50 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/21 16:36:56 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*path;
	char	*temp;
//	char	*cmd;

	path = getenv("PATH");
	temp = get_token(path, ":");
//	cmd = readline(PROMPT);
	while (temp)
	{
		printf("%s\n", temp);
		free(temp);
		temp =get_token(NULL, ":");
	}
	return (0);
}
