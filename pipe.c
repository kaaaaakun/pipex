#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("fd.txt");
	write(1,"a",fd);
	}
