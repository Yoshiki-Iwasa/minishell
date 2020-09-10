/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollor_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 22:14:57 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 13:58:31 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** $ と　{}　が組み合わさった変数を変換する。${} ならindex2から、$OOOならindex１から
** key として考える。
*/

void	convert_bracket_val
	(char **args_i, int start_index, t_list *d_val, t_list *e_val)
{
	char *arg;
	char **splited;
	char *substr;

	arg = *args_i;
	splited = ft_split(arg, '}');
	substr = ft_substr(&splited[0][start_index], \
		0, ft_strlen(&splited[0][start_index]));
	free(splited[0]);
	splited[0] = ft_strjoin("$", substr);
	free(substr);
	trans_each_dollor(splited, d_val, e_val);
	chage_dollor_val_space(splited);
	free(arg);
	arg = joint_strs(splited);
	free_all(splited, 0);
	*args_i = arg;
}

/*
 ** {}で囲まれた変数を変換する関数。{}で必ず囲まれてる前提。
*/

void	change_bracket_val
	(char **args, t_list *d_val, t_list *e_val)
{
	int		i;
	char	*arg;

	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (arg[0] == '$' && arg[1] == '{')
		{
			convert_bracket_val(&args[i], 2, d_val, e_val);
		}
		else if (arg[0] == '{' && arg[1] != '\0')
		{
			convert_bracket_val(&args[i], 1, d_val, e_val);
		}
		i++;
	}
}

int		check_number_of_dollor(char *arg, int *i)
{
	if (is_only_or_many_dollor(arg))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

/*
** split された文字列の先頭に$ をつける。
*/

void	add_dollor_on_head_and_free(char **splited, char *arg)
{
	int		count;
	int		strs_num;
	char	*tmp;

	strs_num = count_strs(splited);
	count = count_dollor(arg);
	while (count)
	{
		tmp = splited[strs_num - 1];
		splited[strs_num - 1] = ft_strjoin("$", splited[strs_num - 1]);
		free(tmp);
		strs_num--;
		count--;
	}
	free(arg);
}

/*
 ** 各文字列中の$変数をリストを参照して変換する関数。リストになければ、$変数のまま。
*/

int		translate_dollor_valiable
	(char **args, t_list *d_val, t_list *e_val)
{
	int		i;
	char	*arg;
	char	**splited;

	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (check_number_of_dollor(arg, &i))
			continue ;
		if (ft_strchr(arg, '$') != 0)
		{
			splited = ft_split(arg, '$');
			add_dollor_on_head_and_free(splited, arg);
			change_bracket_val(splited, d_val, e_val);
			if (!trans_each_dollor(splited, d_val, e_val))
				return (0);
			chage_dollor_val_space(splited);
			arg = joint_strs(splited);
			free_all(splited, 0);
			args[i] = arg;
		}
		i++;
	}
	return (1);
}
