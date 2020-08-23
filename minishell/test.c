#ifdef TEST
#include <unistd.h>

char *cmd1[] = {"cat", "test.c", NULL};
char *cmd2[] = {"head", NULL};
char *cmd3[] = {"grep", "char", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};
int cmd_n = 3;

void dopipes(i) {
  pid_t ret;
  int pp[2] = {};
  if (i == cmd_n - 1) {
    // 左端なら単にexecvp
    execvp(cmds[0][0], cmds[0]);
  }
  else {
    // 左端以外ならpipeしてforkして親が実行、子が再帰
    pipe(pp);
    ret = fork();

    if (ret == 0) {
      // 子プロセスならパイプをstdoutにdup2してdopipes(i+1)で再帰し、
      // 次のforkで親になった側が右からi+1番目のコマンドを実行
      close(pp[0]);
      dup2(pp[1], 1);
      close(pp[1]);
      
      dopipes(i+1);
    }
    else {
      // 親プロセスならパイプをstdinにdup2して、
      // 右からi番目のコマンドを実行
      close(pp[1]);
      dup2(pp[0], 0);
      close(pp[0]);
    
      execvp(cmds[cmd_n-i-1][0], cmds[cmd_n-i-1]);
    }
  }  
}

int main(void) {
  pid_t ret;
  
  ret = fork();
  if (ret == 0)
    dopipes(0);
  else
    wait(NULL);

  return 0;
}

#endif

#ifdef CMP
#include "minishell.h"
int main()
{

printf("result = %d\n", ft_strncmp("TERM_PROGRAM=vscode", "TERM=", 5));
}

#endif

#ifdef OPEN

#include "minishell.h"

void	for_free(char **tmp)
{
	free(tmp);
}
int main()
{
	int fd = open("tttt", O_RDONLY);
	while (1);
	
}
#endif