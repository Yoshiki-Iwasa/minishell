/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_each_dollor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 11:38:06 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 11:59:38 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
// ** d_val の中を探索しに行く。
// */

// int		seek_in_d_val(char **args, t_list *d_val, char *strs[3])
// {
// 	int i;
// 	char	*arg;
// 	char	*tmp;
// 	char	*key;
// 	t_list	*find;
// 	int index;

// 	i = 0; //d_val を確認しに行く
// 	while (args[i])
// 	{
// 		arg = args[i]; //この各arg に対してft_substr でシェル変数部分だけ回収してくる。
// 		if (arg[0] == '$')//echo $KEY のパターン。
// 		{
// 			index = 1;
// 			while (arg[index] == '_' || ft_isalnum(arg[index]) || arg[index] == '?') //'_' か '英数字'のときのみ数える。
// 			{
// 				index++;
// 			}
// 			strs[0] = ft_substr(arg, 0, index);
// 			strs[1] = ft_substr(arg, index, ft_strlen(arg));
// 			strs[2] = NULL; //これ以降、探索はstrs[0] について行う。
// 			key = ft_strjoin(&strs[0][1], "=");
// 			if (!key)
// 				return (0);
// 			if((find = search_entry(d_val, key))) //エントリーを回収してくる。
// 			{
// 				tmp = get_key(find->content); //エントリーの中からkey だけを回収。
// 				free(strs[0]);
// 				strs[0] = find_value(&d_val, tmp);//key に該当するvalue を回収。
// 				triple_free(tmp, key, arg);
// 				args[i] = ft_strjoin(strs[0], strs[1]);
// 				if (args[i][0] == '$')
// 					args[i][0] = 2;
// 				free(strs[0]);
// 				free(strs[1]);
// 			}
// 			else
// 				triple_free(strs[0], strs[1], key);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// /*
// ** e_val の中を探索しに行く。
// */

// int		seek_in_e_val(char **args, t_list *e_val, char *strs[3])
// {
// 	int i;
// 	char	*arg;
// 	char	*tmp;
// 	char	*key;
// 	t_list	*find;
// 	int index;

// 	i = 0;
// 	while (args[i])
// 	{
// 		arg = args[i]; //この各arg に対してft_substr でシェル変数部分だけ回収してくる。
// 		if (arg[0] == '$')//echo $KEY のパターン。
// 		{
// 			index = 1;
// 			while (arg[index] == '_' || ft_isalnum(arg[index])) //'_' か '英数字'のときのみ数える。
// 			{
// 				index++;
// 			}
// 			strs[0] = ft_substr(arg, 0, index);
// 			strs[1] = ft_substr(arg, index, ft_strlen(arg));
// 			strs[2] = NULL; //これ以降、探索はstrs[0] について行う。
// 			key = ft_strjoin(&strs[0][1], "=");
// 			if (!key)
// 				return (0);
// 			if((find = search_entry(e_val, key))) //エントリーを回収してくる。
// 			{
// 				tmp = get_key(find->content); //エントリーの中からkey だけを回収。
// 				free(strs[0]);
// 				strs[0] = find_value(&e_val, tmp);//key に該当するvalue を回収。
// 				triple_free(tmp, key, arg);
// 				args[i] = ft_strjoin(strs[0], strs[1]);
// 				if (args[i][0] == '$')
// 					args[i][0] = 2;
// 				free(strs[0]);
// 				free(strs[1]);
// 			}
// 			else
// 			{
// 				free(strs[0]);
// 				strs[0] = ft_strdup("");
// 				args[i] = ft_strjoin(strs[0], strs[1]);
// 				triple_free(strs[0], strs[1], key);
// 			}
// 		}
// 		i++;
// 	}
// 	return (1);
// }

/*
** 入力の中に＄があるかどうか探す。そして変数リストから検索して値を変換して返す
** e_val と d_val をそれぞれ調べる。
*/

int		trans_each_dollor(char **args, t_list *d_val, t_list *e_val)//key=value 型の時に、ちゃんとno such variableを出せるように。
{
	char *strs[3];

	if (seek_in_d_val(args, d_val, strs) == 0)
		return (0);
	if (seek_in_e_val(args, e_val, strs) == 0)
		return (0);
	return (1);
}