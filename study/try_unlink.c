#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	(void) argc;
	if (!unlink(argv[1]))
		printf("success\n");
	else
		printf("Failed:%s\n", strerror(errno));
	return (0);
}
