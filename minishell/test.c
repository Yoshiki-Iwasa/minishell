// #include "minishell.h"

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

	
// }
// int main(int argc, char **argv, char **envp){
//   int pid;
//   int code;
//   int status;
//   pid_t result;

// 	// printf("matakiteru\n"); //ここまでは一回しか呼ばれないのか

//   pid = fork();
// //   printf("pid = %d\n",pid);
// //   printf("matakiteru\n"); //ここからはもう一回呼ばれる。
//   // fork失敗
//   if(pid == -1){
//     fprintf(stderr, "Error\n\n");
//   }
  
//   // 子プロセスの処理
//   if(pid == 0){
//     printf("Child Process\n");
//     extern char **environ;
// 	 char *argv[2];
//     argv[0] = "ok";
// 	argv[1] = NULL;
//     execve("/bin/ls", argv, envp);
// 	// char *argv[2];
//     //           argv[0] = "ls";
//     //           argv[1] = "./";
//     //           argv[2] = NULL;
// 	// execve(argv[0], argv, environ);
//     printf("%s\n", "子プロセス終了?");
//   }else{
//     printf("Parent Process\n");
    
//     result = wait(&status);
    
//     if(result < 0){
//       fprintf(stderr, "Wait Error.\n\n");
//       exit(-1);
//     }

//     // 終了ステータスのチェック
//     if(WIFEXITED(status)){
//       printf("子プロセス終了");
//       code = WEXITSTATUS(status);
//       printf("コード : %d\n", code);
//     }else{
//       printf("wait失敗");
//       printf("終了コード : %d\n", status);
//     }

//     // シグナルによる終了
//     if (WIFSIGNALED(status)) {
//       printf("シグナル番号：%dによる終了。\n",WTERMSIG(status));
//     }
    
//     printf("親プロセス終了\n");
//   }

//   return 0;
// }
 
// // int main(int argc, char **argv, char **envp)
// // {
// // 	printf("argc = %d\n\n\n", argc);
// // 	int i = 0;
// // 	while (argv[i] != 0)
// // 	{
// // 		printf("argv[%d] = %s\n", i, argv[i]);
// // 		i++;
// // 	}
// // 	write(1, "\n\n", 2);
// // 	i = 0;
// // 	while (envp[i] != 0)
// // 	{
// // 		printf("envp[%d] = %s\n", i, envp[i]);
// // 		i++;
// // 	}
	
// // }