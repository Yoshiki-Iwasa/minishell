

#include "minishell.h"

// int main()
// {
// 	t_list *test;
// 	t_list *new;

// 	test = ft_lstnew("42tokyo");
// 	new = ft_lstnew("42paris");
// 	ft_lstadd_back(&test, new);
// 		new = ft_lstnew("42kansai");
// 	ft_lstadd_back(&test, new);
// 		new = ft_lstnew("42silicon");
// 	ft_lstadd_back(&test, new);
// 		new = ft_lstnew("42unko");
// 	ft_lstadd_back(&test, new);
// 		new = ft_lstnew("42tinko");
// 	ft_lstadd_back(&test, new);


// // }

// void		sig_child(int sig, int pid)
// {
	
// }
#ifdef PIPE
int num = 0;
#include <stdio.h>

  int pipe_fd[2];

  void do_child()
  {
	  
	  write(1, "child\n", 7);
          char    *p = "Hello, dad!!\n";

          printf("this is child\n");

          close(pipe_fd[0]);

          close(1);
          dup2(pipe_fd[1], 1);
          close(pipe_fd[1]);

          while (*p)
                  putchar(*p++);
  }

  void do_parent()
  {
	  	write(1, "parent\n", 7);
          char    c;
          int     count, status;

          printf("this is parent\n");

          close(pipe_fd[1]);

          close(0);
          dup2(pipe_fd[0], 0);
          close(pipe_fd[0]);

          while ((c = getchar()) != EOF)
                  putchar(c);

          if (wait(&status) < 0) {
                  perror("wait");
                  exit(1);
          }
  }

 int main()
  {
          int child;

          if (pipe(pipe_fd) < 0) {
                  perror("pipe");
                  exit(1);
          }

          if ((child = fork()) < 0) {
                  perror("fork");
                  exit(1);
          }

          if (child)
                  do_parent();
          else
                  do_child();
  }
#endif

#ifdef SIG
	int pid;
void		sig_parent(int sig)
{
	printf("親プロセスがシグナルを受け取った\n"); 
	printf("pid = %d\n", pid);
	kill(pid, SIGKILL);
}

void		sig_child(int sig)
{
	printf("子供プロセスがシグナルを受け取っただけ\n");
}

int main(int argc, char **argv, char **envp){
	
	int code;
	int status;
	int sig;
	pid_t result;

	// printf("matakiteru\n"); //ここまでは一回しか呼ばれないのか

  pid = fork();
//   printf("pid = %d\n",pid);
//   printf("matakiteru\n"); //ここからはもう一回呼ばれる。
	
	//ここでシグナルによる条件分岐を入れる。



  // fork失敗
  if(pid == -1){
    fprintf(stderr, "Error\n\n");
  }
  // 子プロセスの処理
  if(pid == 0){
	
	signal(SIGINT, SIG_IGN);
    ft_putendl_fd("Child Process\n", 1);
    extern char **environ;
	 char *argv[2];
	 sleep (10);
    // argv[0] = "ok";
	// argv[1] = NULL;
    // execve("/bin/ls", argv, envp);
	// char *argv[2];
    //           argv[0] = "ls";
    //           argv[1] = "./";
    //           argv[2] = NULL;
	// execve(argv[0], argv, environ);
    printf("%s\n", "子プロセス終了");
  }else{
	signal(SIGINT, sig_parent);
	sleep(5);
   ft_putendl_fd("Parent Process\n", 1);
	printf("子プロセスpid = %d\n", pid); // 最初はここに入ってくるけど

	printf("子プロセスの修理を待ってました。\n");
    result = wait(&status);				//wait があるから子プロセスの終了を待つと
    if(result < 0){
      fprintf(stderr, "Wait Error.\n\n");
      exit(-1);
    }

    //終了ステータスのチェック
    if(WIFEXITED(status)){
      printf("子プロセス終了");
      code = WEXITSTATUS(status);
      printf("コード : %d\n", code);
    }else{
      printf("wait失敗");
      printf("終了コード : %d\n", status);
    }

    // シグナルによる終了
    if (WIFSIGNALED(status)) {
      printf("シグナル番号：%dによる終了。\n",WTERMSIG(status));
    }

    printf("親プロセス終了\n");
  }

  return 0;
}
#endif

#ifdef READ

int main()
{
	char line[260];

	read(0, line, 256);
	printf("\n%d\n", line[0]);
}



#endif

#ifdef TEST

int main()//ファイルディスクリプターの値は変わらないけど、ファイルディスクリプターを複製してくれるから、１、でも３でもアクセスできるようになる。
{
	
	int fd;
	int stdout_fd;

	fd = open("test.txt", O_RDWR | O_APPEND | O_CREAT | S_IREAD | S_IWRITE);
	close(1);
	dup2(fd, 1);
	write(1, "123456789", 9);
}

#endif

#ifdef SIG

int		sig_handle(int sig)
{
	if (sig == SIGINT)
	{
	-	return (1);
	}
	else
	{
		kill 
	}
	
}

int main()//ファイルディスクリプターの値は変わらないけど、ファイルディスクリプターを複製してくれるから、１、でも３でもアクセスできるようになる。
{
	int sig;
	char buf[100];

	signal(sig, sig_handle);
	while (read(0, buf, 15) != 5)
	{
		printf("continue\n");

	}
	
}

#endif