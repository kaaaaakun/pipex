#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
int main() 
{
	  pid_t pid;
  time_t t;
  int status;

	pid_t child1;
	pid_t child2;
    child1 = fork(); 
    child2 = fork(); 
sleep(5);
pid = waitpid(child1, &status, WNOHANG);
    printf("Hello world!\n");
    printf("	c1:%u|ch2:%u\n",child1,child2);
    return 0; 
} 
