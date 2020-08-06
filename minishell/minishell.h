#ifndef MINISHELL_H
#define MINISHELL_H

#define PATH_MAX 2047
#define FUNC_NUM 7

#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"
#include "./libft/libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int	ft_strcmp(const char *s1, const char *s2);
char*	find_value(t_list **val, char *key);
char	*ft_strcat(char *dest, char *src);
int		command_pwd(void);
int	command_cd(char *arg, t_list **e_val);
int	command_exit(void);
int	command_env(t_list **e_val);
int	command_echo(char **args);
void	ft_putendl(void *str);
void	init_e_val_list(t_list **e_val, char **envp);
void	lst_del_connect(t_list **val, char *key ,void (*del)(void*));
void	del_str(void *str);
t_list		*serch_entry(t_list **val, char *key);


#endif