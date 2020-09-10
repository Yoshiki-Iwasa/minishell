/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 08:05:49 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 08:16:48 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX 2047
# define FUNC_NUM 7

# include <unistd.h>
# include <stdio.h>
# include <syslimits.h>
# include "get_next_line.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <signal.h>

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

char			**add_paths_and_change_arg0(char **arg_zero, t_edlist *vals);
char			**change_into_array(t_list *e_val);
char			**check_and_change_equal(char **args);
char			**ft_strsdup(char **args);
char			**get_path(t_list *e_val);
char			*find_value(t_list **val, char *key);
char			*ft_strcat(char *dest, char *src);
char			*get_key(char *arg);
char			*preparation_for_escape(char *line);
char			*joint_strs(char **args);
int				add_dollor(char **args);
int				change_stdin_fd(char *arg, int *fd);
int				change_stdin_fd(char *arg, int *fd);
int				check_if_key_value(char *arg);
int				check_key_str(char *arg);
int				check_redirect_syntax(char **args);
int				child_precess
				(char **args, t_edlist *vals, char **paths, char *origin_arg);
int				command_cd(char *arg, t_list **e_val);
int				command_echo(char **args);
int				command_env(t_list **e_val);
int				command_exit(void);
int				command_export(char **args, t_edlist *vals);
int				command_pwd(void);
int				command_unset(char **args, t_list *e_val, t_list *d_val);
int				commnad_loop(t_edlist vals);
int				count_commands(char **args);
int				count_dollor(char *str);
int				count_execs(char **args);
int				count_pipe(char **args);
int				count_pipe(char **args);
int				count_strs(char **args);
int				count_strs(char **args);
int				deal_redirection(char **args, int *fd);
int				decide_break_or_continue(char *line, int *i);
int				escape_double_q(char *line, char *new_line, int *i, int *j);
int				escape_single_q(char *line, char *new_line, int *i, int *j);
int				exec_each_command(t_edlist vals, char **args, int cmd_num);
int				exec_shell_command
				(char **args, t_edlist *vals, char **paths, char *origin_arg);
int				find_semi_co(char	**args);
int				free_return(char *arg, int rv);
int				ft_isspace(char c);
int				ft_strcmp(const char *s1, const char *s2);
int				init_e_val_list(t_list **e_val, char **envp);
int				is_only_or_many_dollor(char *arg);
int				launch_shell(t_edlist vals, char *line);
int				make_spaces(char *line, char *new_line, int *i, int *j);
int				no_pipe(char **args, t_edlist *vals);
int				pattern_pipe_exist(char **args, t_edlist *vals, int pipe_count);
int				pattern_pipe_not_exit(char **args, t_edlist *vals);
int				read_command(char **line, int *state, t_list *d_val);
int				seek_in_d_val(char **args, t_list *d_val, char *strs[3]);
int				seek_in_e_val(char **args, t_list *e_val, char *strs[3]);
int				shell_execute(char **args, t_edlist *vals);
int				skip_double_q(char *line, int *i, int *quote_count);
int				trans_dollor_valiable
				(char **args, t_list *d_val, t_list *e_val);
int				trans_each_dollor(char **args, t_list *d_val, t_list *e_val);
int				translate_dollor_valiable
				(char **args, t_list *d_val, t_list *e_val);
int				update_shell_value(char **args, t_edlist *vals);
int				update_val(t_list **val, char *arg);
int				when_meets_double_q(char *line, int *i);
int				when_meets_single_q(char *line, int *i);
int				yes_pipe(char **args, t_edlist *vals, int pipe_count);
t_list			*search_entry(t_list *val, char *key);
void			args_into_array(char **args, char ****args_array, int pipe_num);
void			chage_dollor_val_space(char **args);
void			change_semicon_null(char **args, int *semi_co_place);
void			change_stderror_fd_set_null
				(char **args, int *flag_error, int *fd, int *i);
void			change_stderror_fd(char *arg, int *fd);
void			change_stdout_fd_for_append(char *arg, int *fd);
void			change_stdout_fd_set_null_append
				(char **args, int *flag_out, int *fd, int *i);
void			change_stdout_fd_set_null
				(char **arg, int *flag_out, int *fd, int *i);
void			change_stdout_fd(char *arg, int *fd);
void			change_stdout_fd(char *arg, int *fd);
void			close_and_dup2_1(int pp_zero, int pp_one);
void			close_and_dup2_2(int pp_zero, int pp_one);
void			del_str(void *str);
void			del_str(void *str);
void			escape_double(char *line, char *new_line, int *i, int *j);
void			escape_fds(int *stdin_fd, int *stdout_fd, int *stderror_fd);
void			escape_single(char *line, char *new_line, int *i, int *j);
void			fix_args(char **args, char ascii, char c);
void			free_all(char **args, char *line);
void			free_args(char **args, char *line, int arglen);
void			ft_putendl(void *str);
void			insert_unprintable(char *line);
void			lst_del_connect(t_list **val, char *key, void (*del)(void*));
void			pattern_double(char *line, int *i);
void			pattern_single(char *line, int *i);
void			put_error(char *arg);
void			recover_stdinout
				(int in_out, int *stdin_fd, int *stdout_fd, int *stderror_fd);
void			setting_signal(void);
void			sig_handle_bs(int sig);
void			sig_handle_c(int sig);
void			signel_pipe(int sig);
void			triple_free(char *one, char *two, char *three);

#endif
