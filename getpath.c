/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:56:26 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/13 19:56:53 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*getpath(char *command, char **env)
{
	char		**result;
	int			i;

	i = 0;
	if (!command)
		exit (1);
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	result = ft_split(ft_strtrim(env[i], "PATH="), ':');
	if (!result)
		exit (1);
	if (access(ft_strtrim(command, "/./"), X_OK) == 0)
		return (ft_strtrim(command, "/./"));
	return (check_path(command, result));
}
