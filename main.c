/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:09:27 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/13 19:55:38 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (argc != 5)
	{
		ft_putendl_fd("Please enter correct value", 2);
		return (0);
	}
	if (pipe(pipefd) < 0)
		error_exit("pipe");
	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
		firstfork(argv, pipefd, env);
	close_ee(pipefd[1]);
	dup2_ee(pipefd[0], STDIN_FILENO);
	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
		lastfork(argv, pipefd, env);
	waitchild();
}

void	firstfork(char **argv, int *pipefd, char **env)
{
	int		fd;
	char	*path;
	char	**command;

	close_ee(pipefd[0]);
	fd = open_ee(argv[1], O_RDONLY, 0);
	command = ft_split(argv[2], ' ');
	if (!command)
		exit (1);
	path = getpath(ft_strjoin("/", command[0]), env);
	if (!path)
		exit (1);
	dup2_ee(fd, STDIN_FILENO);
	close_ee(fd);
	fd = pipefd[1];
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	execve(path, command, NULL);
}

void	lastfork(char **argv, int *pipefd, char **env)
{
	int		fd;
	char	*path;
	char	**command;

	(void)pipefd;
	fd = open_ee(argv[4], O_CREAT | O_TRUNC | O_WRONLY, \
		S_IRWXU | S_IRWXG | S_IRWXO);
	command = ft_split(argv[3], ' ');
	if (!command)
		exit (1);
	path = getpath(ft_strjoin("/", command[0]), env);
	if (!path)
		exit (1);
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	execve(path, command, NULL);
}

void	waitchild(void)
{
	int	i;
	int	status;

	i = 0;
	while (i < 2)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit(1);
		i++;
	}
	exit(0);
}
