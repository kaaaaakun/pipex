#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd[2];

	pipe(fd);
	printf ("%d/%d",fd[0],fd[1]);
	}
