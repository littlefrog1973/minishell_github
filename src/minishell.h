/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:40:06 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/09/25 14:06:35 by sdeeyien         ###   ########.fr       */
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
# define WHITE_SPACE "\n\r\f\v\t "
# define NUM_BUILTIN 3

/*readline.c*/
char	*readline_wrap(const char *prompt);

/*get_token.c*/
char	*get_token(char *line, char *delimit);

/*utils.c*/
void	perr(char *s);
ssize_t	search_str(char *str[], char *search);
size_t	count_str(char *str[]);
void	free_duo_ptr(char **argc);
ssize_t	new_str(char **env, char *add_line);

/*utils2.c*/
char	**env_dup(char **env, char *add_line);
void	init_fn_ptr(int (*fn_ptr[])(int, char **, char ***), char **list);

/*cd.c*/
int		cd(int argc, char **argv, char ***env);

/*export.c*/
void	set_str(int arc, char *arv[], char *str);
int		export(int argc, char **argv, char ***env);

/*unset.c*/
int		unset(int argc, char **argv, char ***env);

#endif
