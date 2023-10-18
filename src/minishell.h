/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:40:06 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/10/18 01:18:42 by pboonpro         ###   ########.fr       */
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
# define NUM_BUILTIN 6

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

typedef struct s_readline
{
	char				*r_line;
	char				*command;
	int					n_pipe;
	t_file				*infile;
	t_file				*outfile;
	struct s_readline	*next;
}	t_readline;

typedef struct s_exe
{
	char			**cmd;
	int				*fd_in;
	int				size_fd_in;
	int				*fd_out;
	int				size_fd_out;
	int				real_in;
	int				real_out;
	int				size_exe;
}	t_exe;

typedef struct s_pipe
{
	int	*pipe_fd;
	int	size;
}	t_pipe;

/*readline.c*/
char		*readline_wrap(const char *prompt);

/*get_token.c*/
char		*get_token(char *line, char *delimit);
char		*get_token_file(char *line, char *delimit);

/*utils.c*/
void		perr(char *s);
ssize_t		search_str(char *str[], char *search);
size_t		count_str(char *str[]);
void		free_duo_ptr(char **argc);
ssize_t		new_str(char **env, char *add_line);

/*utils2.c*/
char		**env_dup(char **env, char *add_line);
void		init_fn_ptr(int (*fn_ptr[])(int, char **, char ***), char **list);
int			count_char(char *r_line, char to_count);
void		free_ptr(char *argc);

/*cd.c*/
int			cd(int argc, char **argv, char ***env);

/*export.c*/
void		set_str(int arc, char *arv[], char *str);
int			export(int argc, char **argv, char ***env);

/*unset.c*/
int			unset(int argc, char **argv, char ***env);

/*execute.c*/
int			exec(char **argv, char ***envp, int i);

/*minishell.c*/
int			get_fullpath(const char *line, char *full_path, char **env);

/*parsing_1.c*/
// trim white space from front and rear of read_line
// create and init struct t_readline
t_readline	*parsing_line(char *r_line, char **env, int status);

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

/*parsing_util3_1.c*/
t_file		*find_file(char *r_line, char *redi);

/*parsing_util4.c*/
char		*del_in_out2(char *cmd, t_file *infile, t_file *outfile);
void		lstclear_t_file(t_file **lst, void (*del)(void *));
void		free_t_file(t_file *p_file);
void		lstadd_back_t_file(t_file **lst, t_file *new);

/*parsing_util5.c*/
char		*put_env(char *command, char **env, int status);

/*parsing_util5a.c*/
size_t		dup_buf_status(char *buf, size_t i, int status, size_t *k);
void		init_put_env_var(size_t *i, size_t *j, int *s_quote, int *d_quote);
void		set_ds_quote(int *s_quote, int *d_quote, char cmd);

/*parsing_util6.c*/
int			count_pipe_in_quote(char *r_line);
char		**check_pipe_in_quote(char **temp1, char *r_line);

/*echo.c*/
int			echo(int argc, char **argv, char ***env);

/*pwd.c*/
int			pwd(int argc, char **argv, char ***env);

/*env.c*/
int			env(int argc, char **argv, char ***envv);

/*exec_single_buitlin.c*/
int			exec_single_builtin(char **argv, char ***env);

/*redi_utils.c*/
void		free_exe(t_exe **str, int i);
int			ft_filesize(t_file *lst);
int			ft_readlinesize(t_readline *lst);
void		ft_execlear(t_exe *new, t_pipe *p);
void		create_exe(t_exe *new, t_readline *file);

/*redi_check.c*/
int			check_fd_in(char *name);
int			check_fd_out(char *name);
int			check_fd_app(char *name);
int			open_here(char *name, t_readline *file);
void		error_file(char *s, int mode);

/*redi_do.c*/
void		do_here(t_exe *a, t_readline *line);
int			*do_fd_in(t_exe *a, t_readline *file);
int			*do_fd_out(t_exe *a, t_readline *file);

/*redi.c*/
void		main_exe(t_readline *file, int *status, char ***env);
t_exe		*join_exe(t_readline *file);
void		setup_pipe(t_pipe *p, t_exe *a);
void		do_all_redi(t_exe *a, t_pipe *p);
void		do_pipe(int npipe, t_pipe *a);

#endif
