/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:20:36 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/07 16:03:42 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void forkexample()
{
    // child process because return value zero
    if (fork() == 0)
	{
        printf("Hello from Child!\n");
	}
    // parent process because return value non-zero.
    else
	{
        printf("Hello from Parent!\n");
	}
}
int main()
{
    forkexample();
    return 0;
}
