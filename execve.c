#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char    command[] = "/bin/cat";
  char    *exargv[] = {"cat", "-n", "", NULL};
  char    *exenvp[] = {NULL};
  int     return_code = 0;

  if (argc == 2) {
    /* 実行時引数（パス名）をexecveの引数にする */
    exargv[2] = argv[1];
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
//how discover command path
//what is env
//make command atoi
