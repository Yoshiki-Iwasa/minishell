/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:18:11 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/28 16:33:47 by yiwasa           ###   ########.fr       */
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

/*
 **	形が、$key=value または、key=$value になってないかを調べる関数。
*/

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
 ** 文字列を結合させる関数。
*/

char *joint_strs(char **args)
{
	char *ret;
	char *tmp;
	int i;

	i = 0;
	ret = ft_strdup("");
	while (args[i])
	{
		tmp = ret;
		ret = ft_strjoin(ret, args[i]);
		free(tmp);
		i++;
	}
	return (ret);
}

/*
 ** 先頭に無理やり、'$' をつける関数。
*/

int	add_dollor(char **args)
{
	int i;
	char *tmp;

	i = 0;
	while (args[i])
	{
		tmp = args[i];
		if (args[i][0] != '$')
		{
			args[i] = ft_strjoin("$", args[i]);
			free(tmp);
		}
		i++;
	}
	return (1);
}



/*
 ** 存在しない$変数を、空文字列に変えるための関数。
*/

void	chage_dollor_val_space(char **args)
{
	int i;
	char *tmp;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			tmp = args[i];
			args[i] = ft_strdup("");
			free(tmp);
		}
		i++;
	}
}

/*
 ** {}で囲まれた変数を変換する関数。{}で必ず囲まれてる前提。
*/

void	change_bracket_val(char **args, t_list *d_val, t_list *e_val)
{
	int i;
	char *arg;
	char **splited;
	char *substr;

	i = 0;
	while (args[i])
	{
		arg = args[i];
		if (arg[0] == '$' && arg[1] == '{')
		{
			splited = ft_split(arg, '}'); // これで　${TTT / ddd  みたいになった。
			substr = ft_substr(&splited[0][2], 0, ft_strlen(&splited[0][2]));//TTT だけとってくる。　
			free(splited[0]);
			splited[0] = ft_strjoin("$", substr); //これで、$TTT みたいにする。
			trans_each_dollor(splited, d_val, e_val);//これで$TTT の変換完了。
			chage_dollor_val_space(splited);//trans_each_dollorを超えてなお生き残っておるのは変数リストに存在しないやつ。だから消す。
			free(arg);
			arg = joint_strs(splited);
			free_all(splited, 0);
			args[i] = arg;//これで、いけたかな。
		}
		else if (arg[0] == '{')
		{
			splited = ft_split(arg, '}'); // これで　${TTT / ddd  みたいになった。
			substr = ft_substr(&splited[0][1], 0, ft_strlen(&splited[0][1]));//TTT だけとってくる。　
			free(splited[0]);
			splited[0] = ft_strjoin("$", substr); //これで、$TTT みたいにする。
			trans_each_dollor(splited, d_val, e_val);//これで$TTT の変換完了。
			chage_dollor_val_space(splited);//trans_each_dollorを超えてなお生き残っておるのは変数リストに存在しないやつ。だから消す。
			free(arg);
			arg = joint_strs(splited);
			free_all(splited, 0);
			args[i] = arg;//これで、いけたかな。
		}
		i++;
	}
}

/*
 ** 各文字列中の$変数をリストを参照して変換する関数。リストになければ、$変数のまま。
*/

int		translate_dollor_valiable(char **args, t_list *d_val, t_list *e_val)
{
	int i = 0;
	char *arg;
	int flag; //
	char **splited;

	while (args[i])
	{
		arg = args[i];
		flag = 0;
		if (ft_strchr(arg, '$') != 0)
		{
			if (arg[0] == '$')//先頭に$ があるときだけ場合分け。111111111${USER}111111とかに対応するため。
				flag = 1;
			splited = ft_split(arg, '$'); //これで、'$'以前と以後に別れた
			if (flag)
				add_dollor(splited);//これで、分割された変数にふたたび$がついた。
			change_bracket_val(splited,  d_val, e_val);// ${変数}タイプの変数に対応するためのもの。
			free(arg);
			if (!trans_each_dollor(splited, d_val, e_val))// $変数タイプの変換を担当する関数。
				return (0); //ここで、splited のなかの$変数は変換完了。
			chage_dollor_val_space(splited);//trans_each_dollorを超えてなお生き残っておるのは変数リストに存在しないやつ。だから消す。
			arg = joint_strs(splited); //最後に全部くっつけて元通り。　（$DDD$GGG　みたいなときに必要。）
			free_all(splited, 0);
			args[i] = arg;
		}
		i++;
	}
	return (1);
}

/*
	入力の中に＄があるかどうか探す。そして変数リストから検索して値を変換して返す
	e_val と d_val をそれぞれ調べる。
*/

int		trans_each_dollor(char **args, t_list *d_val, t_list *e_val)//key=value 型の時に、ちゃんとno such variableを出せるように。
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
		if (check_if_key_value(arg)) // ここで、key_value なのか確認する。そしたら別処理。export KEY=VALUE のための対策。
		{
			if (check_doller_exit(arg)) //先頭に'$'が入っている、または'=$'の形になっていないか確認。
			{
				//入ってきたら、その文字列をコンバートして、文字列作って、その先頭アドレスを返す。
				// "$変数=value" -> "key=value" 、"key=$変数" -> "key=value", $変数=$変数 -> "key=value"
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
		if (arg[0] == '$')//echo $KEY のパターン。
		{
			key = ft_strjoin(&arg[1], "=");
			if (!key)
				return (0);
			if((find = search_entry(d_val, key)))
			{
				flag = 1;
				free(args[i]);
				args[i] = find_value(&d_val, get_key(find->content));
				free(key);
			}
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
			if (!key)
				return (0);
			if((find = search_entry(e_val, key)))
			{
				flag = 1;
				free(args[i]);
				args[i] = find_value(&e_val, get_key(find->content));
				free(key);
			}
		}
		i++;
	}
	return (1);
}
