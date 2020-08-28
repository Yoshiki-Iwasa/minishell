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
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

typedef	struct	s_edlist
{
	t_list *e_val;
	t_list *d_val;
}				t_edlist;

int		ft_strcmp(const char *s1, const char *s2);
char*	find_value(t_list **val, char *key);
char	*ft_strcat(char *dest, char *src);
int		command_pwd(void);
int		command_cd(char *arg, t_list **e_val);
int		command_exit(void);
int		command_env(t_list **e_val);
int		command_echo(char **args);
void	ft_putendl(void *str);
int		init_e_val_list(t_list **e_val, char **envp);
void	lst_del_connect(t_list **val, char *key ,void (*del)(void*));
void	del_str(void *str);
t_list	*search_entry(t_list *val, char *key);
int		command_export(char **args, t_edlist *vals);
char	*get_key(char *arg);
int		command_unset(char **args, t_list *e_val, t_list *d_val);
int		update_val(t_list **val, char *arg);
int		ft_isspace(char c);
int		check_if_key_value(char *arg);
char	**get_PATH(t_list *e_val);
int		trans_dollor_valiable(char **args, t_list *d_val, t_list *e_val);
int		exec_shell_command(char **args, t_list *e_val, t_list **d_val,char **paths);
int		child_precess(char **args, char **envp, char **paths);
char	**change_into_array(t_list *e_val);
int		count_commands(char **args);
int		find_semi_co(char	**args);
void	escape_double(char *line, char *new_line, int *i, int *j);
void	escape_single(char *line, char *new_line, int *i, int *j);
char	*preparation_for_escape(char *line);
void	fix_args(char **args, char ascii, char c);
void	pattern_double(char *line, int *i);
void	pattern_single(char *line, int *i);
void	insert_unprintable(char *line);
int		deal_redirection(char **args, int *fd);
void	change_stdin_fd(char *arg, int *fd);
void	change_stdout_fd(char *arg, int *fd);
int		find_pipe(char	**args);
void	sig_handle_C(int sig);
void	sig_handle_bs(int sig);
void	setting_signal(void);
int		count_pipe(char **args);
int		no_pipe(char **args, t_edlist *vals, char **paths);
int		yes_pipe(char **args, t_edlist *vals, char **paths, int pipe_count);
int		read_command(char **line);
void	recover_stdinout(int in_out, int *fd, int *stdin_fd, int *stdout_fd);
void	escape_fds(int *stdin_fd, int *stdout_fd);
void	free_all(char **args, char *line);
void	del_str(void *str);
int		shell_execute(char **args, t_edlist *vals, char **paths);
int		exec_each_command(t_edlist vals, char **paths, char **args, int cmd_num);
int		commnad_loop(t_edlist vals, char **paths);
void	change_semicon_null(char **args, int *semi_co_place);
int		translate_dollor_valiable(char **args, t_list *d_val, t_list *e_val);
int		trans_each_dollor(char **args, t_list *d_val, t_list *e_val);//key=value 型の時に、ちゃんとno such variableを出せるように。

#endif