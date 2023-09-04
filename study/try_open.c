#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	int	fd;
	char	buffer[30] = {0};

	if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0)
	{
		printf("%s\n",strerror(errno));
		return (errno);
	}
	printf("opened file's fd = %d\n", fd);
	if (write(fd, "This is a line wrote from try_open.c\n", 37) < 0)
	{
		strerror(errno);
		return (errno);
	}
/*
	read(fd, buffer, 4);
	printf("read buffer = %s", buffer);
*/
	close(fd);
	return (0);
}
