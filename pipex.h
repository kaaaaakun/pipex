/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:56:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/12 15:07:49 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h> 

int		main(int argc, char *argv[]);
void	childfork(char **argv, int *pipefd);
void	parentfork(char **argv, int *pipefd);
char	*getpath(char *command);

void	split_free(char **result);
void	error_exit(char *msg);
int		open_ee(char *str, int oflag, int orflag);
void	dup2_ee(int fd, int std);
void	close_ee(int fd);

#endif
