/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:09:27 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/12 15:20:17 by tokazaki         ###   ########.fr       */
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
		ft_putendl_fd("Please enter correct value", 2);
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
			exit(1);
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
		exit (1);
	path = getpath(ft_strjoin("/", command[0]));
	if (!path)
		exit (1);
	fd = open_ee(argv[1], O_RDONLY, 0);
	dup2_ee(fd, STDIN_FILENO);
	close_ee(fd);
	fd = pipefd[1];
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	close_ee(pipefd[0]);
	execve(path, command, NULL);
}

void	parentfork(char **argv, int *pipefd)
{
	int		fd;
	char	*path;
	char	**command;

	command = ft_split(argv[3], ' ');
	if (!command)
		exit (1);
	path = getpath(ft_strjoin("/", command[0]));
	if (!path)
		exit (1);
	fd = pipefd[0];
	dup2_ee(fd, STDIN_FILENO);
	close_ee(fd);
	fd = open_ee(argv[4], O_CREAT | O_TRUNC | O_WRONLY, \
		S_IRWXU | S_IRWXG | S_IRWXO);
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	close_ee(pipefd[1]);
	execve(path, command, NULL);
}

char	*check_path(char *command, char **result)
{
	int		i;
	char	*path;

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
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(ft_strtrim(command, "/"), STDERR_FILENO);
	return (NULL);
}

char	*getpath(char *command)
{
	extern char	**environ;
	char		**result;
	int			i;

	i = 0;
	if (!command)
		exit (1);
	while (ft_strncmp(environ[i], "PATH=", 5) != 0)
		i++;
	result = ft_split(ft_strtrim(environ[i], "PATH="), ':');
	if (!result)
		exit (1);
	if (access(ft_strtrim(command, "/./"), X_OK) == 0)
		return (ft_strtrim(command, "/./"));
	return (check_path(command, result));
}
