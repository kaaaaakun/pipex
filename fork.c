#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
int exec(int argc);
char *getpath(char *command);

//int main() 
//{
//	  pid_t pid;
//	  pid_t pid2;
//	  time_t t;
//	  int status;
//
//	pid_t child1;
//    child1 = fork(); 
//	if (child1 == 0)
//		exec(2);
//	else
//		waitpid(child1, &status, 0);
//	printf("end\n");
//    return 0; 
//}

#include <stdio.h>
#include <unistd.h>

int exec(int argc)
{
  char    command[] = "/bin/cat";
  char    *exargv[] = {"cat", "-n", "a", NULL};
  char    *exenvp[] = {NULL};
  int     return_code = 0;

  if (argc == 2) {
    /* 実行時引数（パス名）をexecveの引数にする */
 //   exargv[2] = argv[1];
    if (execve(command, exargv, exenvp) == -1) {
      printf("%sコマンドが実行できませんでした\n", command);
      perror("");
      return_code = 1;
    }
  }
  else {
    printf("実行時引数の数が不当です\n");
    return_code = 2;
  }
  printf("引数２個の時にはここには来ない");
  return return_code;
}

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
     #include <unistd.h>
int main(int argc,char *argv[])
{
	pid_t pid;
	char *path;
	char **command;
	int status;
	int fd;
	int pipefd[2];

	pipe(pipefd);
	    // プロセスを作成する
    pid = fork();
    // プロセスの作成に失敗
    if ( pid < 0 ) {
        perror("fork()");
        return -1;
    }

	if (pid == 0)
	{
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
	execve(path, command, NULL);
		}
	else
	{ // 親プロセスの場合は、作成した子プロセスのPIDがリターンされる
        waitpid(pid, &status, 0);

    pid = fork();
	if (pid == 0)
	{
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
	fd = open("out", O_CREAT | O_WRONLY, 0666);
	dup2(fd, 1);
	close(fd);
	execve(path, command, NULL);
	}
	waitpid(pid, &status, 0);
        // 子プロセスの終了を待つ
//        printf ("child process (PID = %d) finished\n", pid);
//		dup2(fd, STDIN_FILENO);
//		close(fd);
//		dup2(fd, 1);
//		close(fd);
//		command = ft_split(argv[3], ' ');
//	path = getpath(ft_strjoin("/", command[0]));
//
//	execve(path, command, NULL);
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
