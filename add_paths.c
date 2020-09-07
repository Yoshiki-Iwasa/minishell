/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:17:53 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/07 14:03:10 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 ** paths に新しいパスを追加する関数。
*/

char	**add_new_path(char *new_path, char **paths)
{
	char **new_paths;
	int i;

	i = 0;
	while(paths[i])
		i++;
	new_paths = malloc(sizeof(char *) * (i + 2));// 新しいpath と NULL分。
	i = 0;
	while (paths[i])
	{
		new_paths[i] = ft_strdup(paths[i]);
		i++;
	}

	new_paths[i] = ft_strdup(new_path);
	i++;
	new_paths[i] = NULL;
	free_all(paths, 0);
	return (new_paths);
}


/*
 ** arg[0]が "." または、 "/" で始まっていたら、paths に相対or 絶対パスを追加。そして、arg[0] をパスなしの実行ファイル名に変える。
*/

char	**add_paths_and_change_arg0(char **argZero, t_edlist *vals)
{
	int i;
	char *execFile_ptr;
	char *new_path;
	char **paths;

	paths = get_path(vals->e_val);
	i = 0;
	if (((*argZero)[0] == '.' || (*argZero)[0] == '/' ) && (*argZero)[1] != '\0')
	{
		free_all(paths, 0);
		i = ft_strlen(*argZero);
		while (i >= 0)
		{
			if ((*argZero)[i] == '/') //パスとして最後のスラッシュを探している。
			{
				execFile_ptr = ft_strdup(&(*argZero)[i + 1]);//	実行ファイル名前の部分。
				new_path = ft_substr(*argZero, 0, i);// スラッシュの一個手前まで取ってくる。
				free(*argZero);
				paths = malloc(sizeof(char*) * 2);
				paths[0] = ft_strdup(new_path);
				paths[1] = NULL;
				*argZero = execFile_ptr;// arg0 を実行ファイル名のみに。
				free(new_path);
				break ;
			}
			i--;
		}
		return (paths);
	}
	else
	{
		return (add_new_path("/", paths));
	}

}
