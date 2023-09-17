/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:40:06 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/15 10:53:35 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <limits.h>

# define PROMPT "minishell$>"

/*readline.c*/
char	*readline_wrap(const char *prompt);

/*get_token.c*/
char	*get_token(char *line, char *delimit);

/*utils.c*/
char	**env_dup(char **env);
ssize_t	search_str(char *str[], char *search);
size_t	count_str(char *str[]);
void	perr(char *s);
void	free_double_pointer(char **temp, int i);


#endif
