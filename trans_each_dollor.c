/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_each_dollor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 11:38:06 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 12:29:34 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 入力の中に＄があるかどうか探す。そして変数リストから検索して値を変換して返す
** e_val と d_val をそれぞれ調べる。
*/

int		trans_each_dollor
	(char **args, t_list *d_val, t_list *e_val)
{
	char *strs[3];

	if (seek_in_d_val(args, d_val, strs) == 0)
		return (0);
	if (seek_in_e_val(args, e_val, strs) == 0)
		return (0);
	return (1);
}
