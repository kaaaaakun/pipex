/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:57:29 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/09 18:26:27 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main(int argc, char** argv)
{
    pid_t pid;
    int status;
    int fd;
 
    // プロセスを作成する
    pid = fork();
    // プロセスの作成に失敗
    if ( pid < 0 ) {
        perror("fork()");
        return -1;
    }
 
    // 子プロセスである場合は、0がリターンされる
    if (pid == 0) {
 
        // ファイルオープン
        fd = open("output", O_CREAT | O_WRONLY, 0666);
 
        /*
         * オープンしたファイルのディスクリプタを
         * 標準出力に複製する
         */
        dup2(fd, 1);
        close(fd); // 作成したディスクリプタはクローズ
 
        /*
         * プロセスを乗せかえる
         * ls の出力結果はファイル output に出力される
         */
        execl("/bin/ls", "ls", (char *)NULL);
 
    } else { // 親プロセスの場合は、作成した子プロセスのPIDがリターンされる
 
        // 子プロセスの終了を待つ
        waitpid(pid, &status, 0);
        printf ("child process (PID = %d) finished\n", pid);
    }
 
    return 0;
}
