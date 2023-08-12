#include <unistd.h>
#include <stdio.h>

int main()
{
	int i = 0;
	while (i < 200000)
		printf("1234567890");
	return (0);
}
