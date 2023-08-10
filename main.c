/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:09:27 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/10 18:11:21 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		status;
	int		pipefd[2];

	if (argc != 5)
	{
		ft_putendl_fd("Please enter correct value", 1);
		return (0);
	}
	if (pipe(pipefd) < 0)
		error_exit("pipe");
	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
		childfork(argv, pipefd);
	else
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) != 0)
			error_exit("fork");
		parentfork(argv, pipefd);
	}
	return (0);
}

void	childfork(char **argv, int *pipefd)
{
	int		fd;
	char	*path;
	char	**command;

	command = ft_split(argv[2], ' ');
	if (!command)
		error_exit("not enough arguments");
	path = getpath(ft_strjoin("/", command[0]));
	fd = open(argv[1], O_RDONLY);
	if (!path || fd < 0)
		error_exit(NULL);
	if (dup2(fd, STDIN_FILENO) < 0)
		error_exit(NULL);
	if (close(fd) < 0)
		error_exit(NULL);
	fd = pipefd[1];
	if (dup2(fd, 1) < 0)
		error_exit(NULL);
	if (close(fd) < 0)
		error_exit(NULL);
	if (close(pipefd[0]) < 0)
		error_exit(NULL);
	execve(path, command, NULL);
}

void	parentfork(char **argv, int *pipefd)
{
	int		fd;
	char	*path;
	char	**command;

	command = ft_split(argv[3], ' ');
	if (!command)
		error_exit("not enough arguments");
	path = getpath(ft_strjoin("/", command[0]));
	fd = pipefd[0];
	if (dup2(fd, STDIN_FILENO) < 0 || !path)
		error_exit(NULL);
	if (close(fd) < 0)
		error_exit("close");
	fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, \
		S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		error_exit(NULL);
	if (dup2(fd, 1) < 0)
		error_exit("dup2");
	if (close(fd) < 0)
		error_exit("close");
	if (close(pipefd[1]) < 0)
		error_exit("close");
	execve(path, command, NULL);
}

char	*getpath(char *command)
{
	extern char	**environ;
	char		**result;
	char		*path;
	int			i;

	i = 0;
	if (!command)
		exit (0);
	while (ft_strncmp(environ[i], "PATH=", 5) != 0)
		i++;
	result = ft_split(ft_strtrim(environ[i], "PATH="), ':');
	i = 0;
	while (result[i] != NULL)
	{
		result[i] = ft_strjoin(result[i], command);
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
