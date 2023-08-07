/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:26:24 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/07 14:55:14 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

int main(void)
{
	extern char** environ;
	char **result;
    // environ を使用して環境変数を表示する例
    int i = 0;
    while (ft_strncmp(environ[i], "PATH=",5) != 0) {
//        printf("%i:%s\n",i, environ[i]);
        i++;
    }
	result = ft_split(ft_strtrim(environ[i], "PATH="), ':');
	i = 0;
	while (result[i] != NULL)
	{
        printf("%i:%s\n",i, result[i]);
		i++;
	}

    return 0;
}
