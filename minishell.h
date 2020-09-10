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
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

typedef	struct	s_edlist
{
	t_list *e_val;
	t_list *d_val;
}				t_edlist;

typedef struct	s_flags
{
	int flag_in;
	int flag_out;
	int flag_error;
}				t_flags;

typedef struct	s_fds
{
	int	fd;
	int	stdin_fd;
	int	stdout_fd;
	int	stderror_fd;
	int	fd_flag;
	int rv;
}				t_fds;

int		ft_strcmp(const char *s1, const char *s2);
char	**ft_strsdup(char **args);
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
char	**get_path(t_list *e_val);
int		trans_dollor_valiable(char **args, t_list *d_val, t_list *e_val);
int		exec_shell_command(char **args, t_edlist *vals, char **paths, char *origin_arg);
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
int				deal_redirection(char **args, int *fd);
int	 	change_stdin_fd(char *arg, int *fd);
void	change_stdout_fd(char *arg, int *fd);
void	sig_handle_c(int sig);
void	sig_handle_bs(int sig);
void	setting_signal(void);
int		count_pipe(char **args);
int		no_pipe(char **args, t_edlist *vals);
int		yes_pipe(char **args, t_edlist *vals, int pipe_count);
int		read_command(char **line, int *state, t_list *d_val);
void	recover_stdinout(int in_out, int *stdin_fd, int *stdout_fd, int *stderror_fd);
void	escape_fds(int *stdin_fd, int *stdout_fd, int *stderror_fd);
void	free_all(char **args, char *line);
void	del_str(void *str);
int		shell_execute(char **args, t_edlist *vals);
int		exec_each_command(t_edlist vals, char **args, int cmd_num);
int		commnad_loop(t_edlist vals);
void	change_semicon_null(char **args, int *semi_co_place);
int		translate_dollor_valiable(char **args, t_list *d_val, t_list *e_val);
int		trans_each_dollor(char **args, t_list *d_val, t_list *e_val);//key=value 型の時に、ちゃんとno such variableを出せるように。
char	**add_paths_and_change_arg0(char **argZero, t_edlist *vals);
void	free_args(char **args, char *line, int arglen);
int		count_strs(char **args);
void	change_stdout_fd(char *arg, int *fd);
int		change_stdin_fd(char *arg, int *fd);
void	change_stdout_fd_for_append(char *arg, int *fd);
void	change_stderror_fd(char *arg, int *fd);
void change_stdout_fd_set_null(char **arg, int *flag_out, int *fd, int *i);
void change_stdout_fd_set_null_append(char **args, int *flag_out, int *fd, int *i);
void change_stderror_fd_set_null(char **args, int *flag_error, int *fd, int *i);
int		free_return(char *arg, int rv);
void	signel_pipe(int sig);
char		**check_and_change_equal(char **args);
int		check_key_str(char *arg);
int		count_execs(char **args);
int		count_pipe(char **args);
void	args_into_array(char **args, char ****args_array, int pipe_num);
int		launch_shell(t_edlist vals, char *line);
int		check_redirect_syntax(char **args);
void	put_error(char *arg);
int		pattern_pipe_not_exit(char **args, t_edlist *vals);
int		pattern_pipe_exist(char **args, t_edlist *vals, int pipe_count);
int		update_shell_value(char **args, t_edlist *vals);
int		skip_double_q(char *line, int *i, int *quote_count);
int		decide_break_or_continue(char *line, int *i);
int		escape_double_q(char *line, char *new_line, int *i, int *j);
int		make_spaces(char *line, char *new_line, int *i, int *j);
int	escape_single_q(char *line, char *new_line, int *i, int *j);
int		when_meets_single_q(char *line, int *i);
int		when_meets_double_q(char *line, int *i);
void	close_and_dup2_2(int pp_zero, int pp_one);
void	close_and_dup2_1(int pp_zero, int pp_one);
int	child_precess(char **args, t_edlist *vals, char **paths, char *origin_arg);


#endif