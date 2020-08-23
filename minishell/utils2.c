/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:18:11 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/23 10:41:22 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	環境変数PATH に含まれているpath達を分離する関数
*/
char		**get_PATH(t_list *e_val)
{
	char *cmd_path;
	char **tmp;

	cmd_path = find_value(&e_val, "PATH"); // find が失敗したら、0 が帰ってくるので、そのエラー処理をする必要あり。
	tmp = ft_split(cmd_path, ':');
	free(cmd_path);
	return (tmp);
}

/**
 *		形が、$key=value または、key=$value になってないかを調べる関数。
 * **/

int		check_doller_exit(char *arg)
{
	int i = 0;

	if (arg[0] == '$')
		return (1);
	while (arg[i] != '\0')
	{
		if (arg[i] == '=' && arg[i + 1] == '$')
			return (1);
		i++;
	}
	return (0);
}

/*
	$key=$value の様になっている文字列を key=value の形に治す
*/

char	*convert_key_value(char **args, int index, t_list *d_val) // まず、split して文字列分けるとこから。
{
	char **tmp_args; //key , value の文字列を格納する関数。
	char *join_1;
	char *join_2;
	t_list *find;
	int	i;

	tmp_args = ft_split(args[index], '=');
	i = 0;
	while (tmp_args[i] != NULL)
	{
		if (tmp_args[i][0] == '$')
		{
			if((find = search_entry(d_val, &tmp_args[i][1])))
			{
				free(tmp_args[i]);
				tmp_args[i] = find_value(&d_val, get_key(find->content));
			}
			else
			{
				ft_putstr_fd(tmp_args[i], 1);
				ft_putendl(" : No such valiable :)");
				return (0);
			}
		}
		i++;
	}// ここで、kye,とvalue の変換が完了する。次は、"=" とつなげて返す。
	join_1 = ft_strjoin(tmp_args[0], "=");
	free(tmp_args[0]);
	join_2 = ft_strjoin(join_1, tmp_args[1]);
	free(tmp_args[1]);
	free(join_1);
	free(tmp_args);
	if (!join_1 || !join_2)
		return (0);
	return (join_2);


}
/*
	入力の中に＄があるかどうか探す。そして変数リストから検索して値を変換して返す
*/

int		trans_valiable(char **args, t_list *d_val, t_list *e_val)//key=value 型の時に、ちゃんとno such variableを出せるように。
{
	int		i;
	char	*arg;
	char	*tmp;
	char	*key;
	int		flag;
	t_list	*find;

	flag = 0;
	i = 0; //d_val を確認しに行く
	while (args[i])
	{
		arg = args[i];
		if (check_if_key_value(arg)) // ここで、key_value なのか確認する。そしたら別処理。
		{
			if (check_doller_exit(arg)) //先頭か、= の直後に "$" が入ってないか確認する。
			{
				//入ってきたら、その文字列をコンバートして、文字列作って、その先頭アドレスを返す。
				tmp = convert_key_value(args, i, d_val);
				free(args[i]);
				args[i] = tmp;
				i++;
				continue;
			}
			else
			{
				i++;
				continue; // 次の文字列へ。
			}

		}
		if (arg[0] == '$')
		{
			key = ft_strjoin(&arg[1], "=");
			if((find = search_entry(d_val, key)))
			{
				flag = 1;
				free(args[i]);
				args[i] = find_value(&d_val, get_key(find->content));
			}
			// else
			// {
			// 	ft_putstr_fd(args[i], 1);
			// 	ft_putendl(" : No such valiable :)");
			// 	return (0);
			// }
		}
		i++;
	}
	// e_val を確認しにいく。
	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (check_if_key_value(arg)) // ここで、key_value なのか確認する。そしたら別処理。
		{
			if (check_doller_exit(arg)) //先頭か、= の直後に "$" が入ってないか確認する。
			{
				//入ってきたら、その文字列をコンバートして、文字列作って、その先頭アドレスを返す。
				tmp = convert_key_value(args, i, e_val);
				free(args[i]);
				args[i] = tmp;
				i++;
				continue;
			}
			else
			{
				i++;
				continue; // 次の文字列へ。
			}

		}
		if (arg[0] == '$')
		{
			key = ft_strjoin(&arg[1], "=");
			if((find = search_entry(e_val, key)))
			{
				flag = 1;
				free(args[i]);
				args[i] = find_value(&e_val, get_key(find->content));
			}
			// else
			// {
			
			// }
		}
		i++;
	}
	// if (!flag)
	// {
	// 	ft_putendl("No such valiable :)");
	// 	return (0);
	// }
	
	return (1);
}
