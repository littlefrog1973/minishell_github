#include "color.h"
#include "stdio.h"
#include "minishell.h"


// int main() {
// 	print_debug("hello world\n");
// 	return 0;
// }

void	print_line() {
	printf("\n");
}

void	print_cmd(t_readline *a) {
	printf("cmd: %s", a->command);
	print_line();
}

void	print_infile(t_readline *a) {
	t_file	*tmp;

	tmp = a->infile;
	printf("infile :");
	if (!tmp)
		printf("(null)");
	while (tmp) {
		if (tmp->type == INFILE)
			printf(" %s", tmp->filename);
		tmp = tmp->next;
	}
	print_line();
}

void	print_outfile(t_readline *a) {
	t_file	*tmp;

	tmp = a->outfile;
	printf("outfile :");
	if (!tmp)
		printf("(null)");
	while (tmp) {
		if (tmp->type == OUTFILE)
			printf(" %s", tmp->filename);
		tmp = tmp->next;
	}
	print_line();
}

void	print_heredoc(t_readline *a) {
	t_file	*tmp;

	tmp = a->infile;
	printf("heredoc :");
	if (!tmp)
		printf("(null)");
	while (tmp) {
		if (tmp->type == HEREDOC)
			printf(" %s", tmp->filename);
		tmp = tmp->next;
	}
	print_line();
}

void	print_npipe(t_readline *a) {
	printf("npipe: %d", a->n_pipe);
	print_line();
}

void	print_rline(t_readline *a) {
	printf("rline: %s", a->r_line);
	print_line();
}

void	print_table(t_readline *a) {

	t_readline *tmp;
	int i = 1;
	tmp = a;
	while (tmp) {
		printf("table %d\n", i++);
		print_cmd(tmp);
		print_infile(tmp);
		print_outfile(tmp);
		print_heredoc(tmp);
		print_npipe(tmp);
		print_rline(tmp);
		print_line();
		print_line();

		tmp = tmp->next;
	}
}
