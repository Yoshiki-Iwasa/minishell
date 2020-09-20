/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 08:11:05 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/20 12:05:50 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	put_error_return1225(char *argzero)
{
	ft_putstr_fd("bash: exit:", 2);
	ft_putstr_fd(argzero, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (1255);
}

static int	put_error_return2001(void)
{
	ft_putstr_fd("bash: exit: too many arguments\n", 1);
	return (2001);
}

static int	return_rv_plus_1000(t_edlist *vals)
{
	int		num;
	char	*value;

	value = find_value(&(vals->d_val), "?=");
	num = ft_atoi(value);
	free(value);
	return (1000 + num);
}

/*
** args にはexit の引数が送られて来る。
** まずは、引数なしなら、今の終了ステータスでexit
** args の第一引数が 数字じゃないー＞error吐いてexit
** args の 第一引数が数字で、かつ引数の数が１以上だったときは errorはいて、exit しない。終了ステータスは１
** args の引数が数字だった場合
** 0~255 なら、1000+ 数値でreturn
** 負の値なら、-1 * 数値 + 返り値 = 256 になるようにreturn
** 256~ だったら、256の剰余を返す。
*/

int			command_exit(char **args, t_edlist *vals)
{
	int		num;

	ft_putendl("exit");
	if (args[0] == NULL)
		return (return_rv_plus_1000(vals));
	if ((!is_only_digit(args[0])))
		return (put_error_return1225(args[0]));
	if (is_only_digit(args[0]) && count_strs(args) > 1)
		return (put_error_return2001());
	if (is_only_digit(args[0]))
	{
		num = ft_atoi(args[0]);
		if (0 <= num && num <= 255)
			return (num + 1000);
		else if (num >= 256)
			return (num % 256 + 1000);
		else
			return (1000 + (256 - (num * -1)));
	}
	return (1000);
}
