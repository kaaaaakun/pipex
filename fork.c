#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
int exec(int argc);
char *getpath(char *command);

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
     #include <unistd.h>
void	childfork(char **argv, int *pipefd)
{
	int		fd;
	char	*path;
	char	**command;

	command = ft_split(argv[2], ' ');
	for (int i = 0;command[i] != NULL;i++)
	{
		printf("%d:[%s]000\n",i,command[i]);
	}
	path = getpath(ft_strjoin("/", command[0]));
	printf("[%s][%d/%d]\n", path,pipefd[0],pipefd[1]);
	fd = open(argv[1], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	fd = pipefd[1];
	dup2(fd, 1);
	close(fd);
	close(pipefd[0]);
	execve(path, command, NULL);
}

void	parentfork(char **argv, int *pipefd)
{
	int		fd;
	char	*path;
	char	**command;
	
	command = ft_split(argv[3], ' ');
	for (int i = 0;command[i] != NULL;i++)
	{
		printf("%d:[%s]000\n",i,command[i]);
	}
	path = getpath(ft_strjoin("/", command[0]));
	printf("[%s][%d/%d]\n", path,pipefd[0],pipefd[1]);
	fd = pipefd[0];
	dup2(fd, STDIN_FILENO);
	close(fd);
	fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY , 0660);
	dup2(fd, 1);
	close(fd);
	close(pipefd[1]);
	execve(path, command, NULL);
}

int main(int argc,char *argv[])
{
	pid_t pid;
	int status;
	int pipefd[2];

	if (pipe(pipefd) < 0)
	{
        perror ("pipe()");
		return (0);
	}
    pid = fork();
    if (pid < 0)
	{
        perror("fork()");
        return (0);
    }
	if (pid == 0)
	{
		childfork(argv, pipefd);
	}
	else
	{
		waitpid(pid, &status, 0);
		parentfork(argv, pipefd);
    }
	return (0);
}

void split_free(char **result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

char *getpath(char *command)
{
	extern char** environ;
	char **result;
	char *path;
    int i = 0;
    while (ft_strncmp(environ[i], "PATH=",5) != 0) {
        i++;
    }
	result = ft_split(ft_strtrim(environ[i], "PATH="), ':');
	i = 0;
	while (result[i] != NULL)
	{
		result[i] = ft_strjoin(result[i], command);
		printf("%i:%s[%d]\n",i, result[i], access(result[i], X_OK));
		if (access(result[i], X_OK) == 0)
		{
			path = ft_strdup(result[i]);
			split_free(result);
			return (path);
		}
		i++;
	}
	split_free(result);
	return (NULL);
}
