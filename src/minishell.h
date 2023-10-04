/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:40:06 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/04 11:40:54 by sdeeyien         ###   ########.fr       */
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

# define NONE 0
# define INFILE 1
# define OUTFILE 2
# define APPEND 3
# define HEREDOC 4
# define MAX_PIPE 1024
# define WORD_LEN 1024

typedef struct s_file
{
	char			*filename;
	int				type;
	struct s_file	*next;
}	t_file;

typedef	struct s_readline
{
	char				*r_line;
	char				*command;
	int					n_pipe;
	t_file				*infile;
	t_file				*outfile;
	struct s_readline	*next;
}	t_readline;




/*readline.c*/
char	*readline_wrap(const char *prompt);

/*get_token.c*/
char	*get_token(char *line, char *delimit);
char	*get_token_file(char *line, char *delimit);

/*utils.c*/
void	perr(char *s);
ssize_t	search_str(char *str[], char *search);
size_t	count_str(char *str[]);
void	free_duo_ptr(char **argc);
ssize_t	new_str(char **env, char *add_line);

/*utils2.c*/
char	**env_dup(char **env, char *add_line);
void	init_fn_ptr(int (*fn_ptr[])(int, char **, char ***), char **list);
int		count_char(char *r_line, char to_count);

/*cd.c*/
int		cd(int argc, char **argv, char ***env);

/*export.c*/
void	set_str(int arc, char *arv[], char *str);
int		export(int argc, char **argv, char ***env);

/*unset.c*/
int		unset(int argc, char **argv, char ***env);

/*execute.c*/
int	exec(char **argv, char ***envp, int i);

/*minishell.c*/
int	get_fullpath(const char *line, char *full_path, char **env);

/*parsing.c*/
// trim white space from front and rear of read_line
// create and init struct t_readline
t_readline	*parsing_line(char *r_line, char **env);

/*parsing_util.c*/
int			init_t_file(t_file **file);
t_readline	*init_parse_line(void);
size_t		word_len(char *str);
char		*trim_line(char *read_line);
int			count_pipe(char *r_line);

/*parsing_util2.c*/
void		free_t_readline(t_readline *p_line);
char		*del_in_out(char *command, t_file *infile, t_file *outfile);
void		lstadd_back_r_line(t_readline **lst, t_readline *new);
void		lstclear_r_line(t_readline **lst, void (*del)(t_readline *));

/*parsing_util3.c*/
void		free_t_file(t_file *p_file);
void		lstadd_back_t_file(t_file **lst, t_file *new);
void		lstclear_t_file(t_file **lst, void (*del)(void *));
t_file		*find_infile2(char *r_line);
t_file		*find_outfile2(char *r_line);

/*parsing_util4.c*/
char	*del_in_out2(char *cmd, t_file *infile, t_file *outfile);

#endif
