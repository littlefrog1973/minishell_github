/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:00:19 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/04 23:05:49 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_lst_file(char *cmd, t_file *infile)
{
	while (1)
	{
		ft_memset(ft_strnstr(cmd, infile->filename, ft_strlen(cmd)),
			' ', ft_strlen(infile->filename));
		if (infile->next == NULL)
			break ;
		infile = infile->next;
	}
}

char	*del_in_out2(char *ccmd, t_file *infile, t_file *outfile)
{
	ssize_t	i;
	char	*cmd;
	char	*to_return;

	cmd = ft_strdup(ccmd);
	if (!cmd)
		return (perror("parsing"), NULL);
	if (infile)
		set_lst_file(cmd, infile);
	if (outfile)
		set_lst_file(cmd, outfile);
	i = -1;
	while (cmd[++i])
		if (cmd[i] == '<' || cmd[i] == '>')
			cmd[i] = ' ';
	to_return = ft_strtrim(cmd, " ><");
	if (!to_return)
		return (perror("parsing"), free(cmd), NULL);
	return (free(cmd), to_return);
}
