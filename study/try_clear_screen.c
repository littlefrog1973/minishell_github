#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

void	type_prompt()
{
	static int	first_time = 1;
	if (first_time)
	{
		const char *CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		first_time = 0;
	}
	printf("#");
}

int	main(void)
{
	char	*r_line;

	while (1)
	{
		type_prompt();
		r_line = readline(r_line);
		printf("command = %s\n");
		sleep(3);
	}
	return (0);
}
