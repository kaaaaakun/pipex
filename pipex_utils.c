/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:17:45 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/15 16:41:56 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	split_free(char **result)
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

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

int	open_ee(char *str, int oflag, int orflag)
{
	int	fd;

	fd = open(str, oflag, orflag);
	if (fd < 0)
	{
		perror(str);
		exit (1);
	}
	return (fd);
}

void	dup2_ee(int fd, int std)
{
	int	flag;

	flag = dup2(fd, std);
	if (flag < 0)
	{
		perror("dup2");
		exit (1);
	}
}

void	close_ee(int fd)
{
	int	flag;

	flag = close(fd);
	if (flag < 0)
	{
		perror("close");
		exit (1);
	}
}
