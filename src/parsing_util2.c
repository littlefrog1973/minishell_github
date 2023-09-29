/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:54:19 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/29 15:03:41 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_t_readline(t_readline *p_line)
{
	if (!p_line)
		return (1);
	else
	{
		if (p_line->r_line)
			free(p_line->r_line);
		if (p_line->command)
			free_duo_ptr(p_line->command);
		if (p_line->infile)
		{
			if (p_line->infile->filename)
				free(p_line->infile->filename);
			free(p_line->infile);
		}
		if (p_line->outfile)
		{
			if (p_line->outfile->filename)
				free(p_line->outfile->filename);
			free(p_line->outfile);
		}
		free(p_line);
	}
	return (0);
}

char	**del_in_out(char **cmd, t_file *infile, t_file *outfile)
{
	char	*move_pos;
	size_t	n_str;

	if (infile)
	{
		move_pos = ft_strnstr(cmd[0], infile->filename, ft_strlen(cmd[0]));
		move_pos += ft_strlen(infile->filename);
		while (!ft_isalnum(*(move_pos)))
			move_pos++;
		ft_memmove(cmd[0], move_pos, ft_strlen(move_pos) + 1);
	}
	if (outfile)
	{
		n_str = count_str(cmd);
		move_pos = ft_strrchr(cmd[n_str - 1], '>');
		if (move_pos && *(move_pos - 1) == '>')
			*(move_pos - 1) = '\0';
		else
			*move_pos = '\0';
		move_pos--;
		while (ft_isspace(*(move_pos)))
			move_pos--;
		*(++move_pos) = '\0';
	}
	return (cmd);
}
