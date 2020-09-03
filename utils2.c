/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 09:18:11 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/04 07:50:20 by yiwasa           ###   ########.fr       */
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
	if (!ft_strcmp(cmd_path, "not_found"))
	{
		tmp = malloc(sizeof(char*) * 2);
		tmp[0] = ft_strdup("");
		tmp[1] = NULL;
		return (tmp);
	}
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

// /*
//  ** シェル変数に使ない文字が来た段階で文字列を分割し、必要なぶんだけ格納する。
// */

// char	**devide_arg(char *arg)//まず、
// {
// 	int i;
// 	char **ret;
// 	char *tmp;
// 	char charset[2];

// 	i = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] != '_' && !ft_isalnum(arg[i])) //shell 変数に使えない文字が来た。
// 		{
// 			charset[0] = arg[i];
// 			charset[1] = '\0'; //後で結合するための文字列作成。
// 			ret = ft_split(arg, charset[0]); // c で分割。これではこまるか。。。。
// 			// *tmp = 　　　　　　
// 		}
// 		i++;
// 	}
// }

/*
	$key=$value の様になっている文字列を key=value の形に治す
*/

char	*convert_key_value(char **args, int index, t_list *d_val) // まず、split して文字列分けるとこから。
{
	char **tmp_args; //key , value の文字列を格納する関数。
	char *join_1;
	char *join_2;
	// char **tmp_strs;
	t_list *find;
	int	i;

	tmp_args = ft_split(args[index], '=');
	i = 0;
	while (tmp_args[i] != NULL)
	{
		if (tmp_args[i][0] == '$')
		{
			//serch_entry で探す前にシェル変数を分割して、search したあとjoin。
			// tmp_strs = devide_arg(&tmp_args[i][1]);
			if ((find = search_entry(d_val, &tmp_args[i][1])))
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
			splited = ft_split(arg, '}'); // これで${TTT / ddd  みたいになった。
			substr = ft_substr(&splited[0][2], 0, ft_strlen(&splited[0][2]));//TTT だけとってくる。
			free(splited[0]);
			splited[0] = ft_strjoin("$", substr); //これで、$TTT みたいにする。
			free(substr);
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
			free(substr);
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
 ** 文字列中の、'$'の数を数える関数
*/

int		count_dollor(char *str)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int		count_strs(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i);
}

int		is_only_or_many_dollor(char *arg)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			count++;
		}
		i++;
	}
	if ((count == 1 && i == 1) || count > 1)
		return (1);
	return (0);
}

/*
 ** 各文字列中の$変数をリストを参照して変換する関数。リストになければ、$変数のまま。
*/

int		translate_dollor_valiable(char **args, t_list *d_val, t_list *e_val)
{
	int i = 0;
	char *arg;
	int flag;
	char **splited;
	int count;
	int strs_num;
	char *tmp;

	while (args[i])
	{
		arg = args[i];
		if (is_only_or_many_dollor(arg))
		{
			i++;
			continue ;
		}
		flag = 0;
		if (ft_strchr(arg, '$') != 0)
		{
			count = count_dollor(arg); //何個$ があるかを確認。
			// if (arg[0] == '$')//先頭に$ があるときだけ場合分け。111111111${USER}111111とかに対応するため。
			// 	flag = 1;
			splited = ft_split(arg, '$'); //これで、'$'以前と以後に別れた <-ここまでは悪くない気がする。
			//この後にうしろから順次$ を結合させていく。
			strs_num = count_strs(splited);
			while (count)
			{
				tmp = splited[strs_num - 1];
				splited[strs_num - 1] = ft_strjoin("$", splited[strs_num - 1]);
				free(tmp);
				strs_num--;
				count--;
			} // これで、$を含んだ形でsplit をすることができた。
			//次は、各splited に対して、変換を行いたいところ。
			// if (flag)
			// 	add_dollor(splited);//これで、分割された変数にふたたび$がついた。
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
	char *strs[3];
	int index;
	//　この中で、$KKK:555555 みたいなのがあったら、 分割して、探索する必要がある。
	// そうすれば、key=value 型かどうかなんて気にする必要ない
	flag = 0;
	i = 0; //d_val を確認しに行く
	while (args[i])
	{
		arg = args[i]; //この各arg に対してft_substr でシェル変数部分だけ回収してくる。
		if (arg[0] == '$')//echo $KEY のパターン。
		{
			//そしたら、どこまでをshell変数として見なくては行けないかをかぞえてくる。
			//そして分割。
			index = 1;
			while (arg[index] == '_' || ft_isalnum(arg[index]) || arg[index] == '?') //'_' か '英数字'のときのみ数える。
			{
				index++;
			}
			strs[0] = ft_substr(arg, 0, index);
			strs[1] = ft_substr(arg, index, ft_strlen(arg));
			strs[2] = NULL; //これ以降、探索はstrs[0] について行う。
			key = ft_strjoin(&strs[0][1], "=");
			if (!key)
				return (0);
			if((find = search_entry(d_val, key))) //エントリーを回収してくる。
			{
				flag = 1;
				tmp = get_key(find->content); //エントリーの中からkey だけを回収。
				free(strs[0]);
				strs[0] = find_value(&d_val, tmp);//key に該当するvalue を回収。
				free(tmp);
				free(key);
				free(arg);
				args[i] = ft_strjoin(strs[0], strs[1]);
				free(strs[0]);
				free(strs[1]);
			}
			else
			{
				free(strs[0]);
				// strs[0] = ft_strdup("");
				// args[i] = ft_strjoin(strs[0], strs[1]);
				// free(strs[0]);
				free(strs[1]);
				free(key);
			}
		}
		i++;
	}
	// e_val を確認しにいく。
	i = 0; //d_val を確認しに行く
	while (args[i])
	{
		arg = args[i]; //この各arg に対してft_substr でシェル変数部分だけ回収してくる。
		if (arg[0] == '$')//echo $KEY のパターン。
		{
			//そしたら、どこまでをshell変数として見なくては行けないかをかぞえてくる。
			//そして分割。
			index = 1;
			while (arg[index] == '_' || ft_isalnum(arg[index])) //'_' か '英数字'のときのみ数える。
			{
				index++;
			}
			strs[0] = ft_substr(arg, 0, index);
			strs[1] = ft_substr(arg, index, ft_strlen(arg));
			strs[2] = NULL; //これ以降、探索はstrs[0] について行う。
			key = ft_strjoin(&strs[0][1], "=");
			if (!key)
				return (0);
			if((find = search_entry(e_val, key))) //エントリーを回収してくる。
			{
				flag = 1;
				tmp = get_key(find->content); //エントリーの中からkey だけを回収。
				free(strs[0]);
				strs[0] = find_value(&e_val, tmp);//key に該当するvalue を回収。
				free(tmp);
				free(key);
				free(arg);
				args[i] = ft_strjoin(strs[0], strs[1]);
				free(strs[0]);
				free(strs[1]);
			}
			else
			{
				free(strs[0]);
				strs[0] = ft_strdup("");
				args[i] = ft_strjoin(strs[0], strs[1]);
				free(strs[0]);
				free(strs[1]);
				free(key);
			}
		}
		i++;
	}
	return (1);
}
