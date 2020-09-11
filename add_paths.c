/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:17:53 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 15:54:29 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** paths に新しいパスを追加する関数。
*/

char	**add_new_path(char *new_path, char **paths)
{
	char	**new_paths;
	int		i;

	i = 0;
	while (paths[i])
		i++;
	new_paths = malloc(sizeof(char *) * (i + 2));
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
** ルートディレクトリのパスを追加（ルートディレクトリのみのパスにする）関数
*/

int		add_root_path(char **arg_zero, char ***paths, int i)
{
	char *exec_file_ptr;
	char *new_path;

	if ((*arg_zero)[i] == '/')
	{
		exec_file_ptr = ft_strdup(&(*arg_zero)[i + 1]);
		new_path = ft_substr(*arg_zero, 0, i);
		free(*arg_zero);
		(*paths) = malloc(sizeof(char*) * 2);
		(*paths)[0] = ft_strdup(new_path);
		(*paths)[1] = NULL;
		*arg_zero = exec_file_ptr;
		free(new_path);
		return (0);
	}
	return (1);
}

/*
** arg[0]が "." または、 "/" で始まっていたら、paths に相対or 絶対パスを追加。
** そして、arg[0] をパスなしの実行ファイル名に変える。
*/

char	**add_paths_and_change_arg0(char **arg_zero, t_edlist *vals)
{
	int		i;
	char	**paths;

	paths = get_path(vals->e_val);
	if (paths[0][0] == '\0')
	{
		free_all(paths, 0);
		paths = get_path(vals->d_val);
	}
	i = 0;
	if (((*arg_zero)[0] == '.' && (*arg_zero)[1] != '\0') || \
	((*arg_zero)[0] == '/' && (*arg_zero)[1] != '\0' && paths[0][0] != '\0'))
	{
		free_all(paths, 0);
		i = ft_strlen(*arg_zero);
		while (i >= 0)
		{
			if (add_root_path(arg_zero, &paths, i) == 0)
				break ;
			i--;
		}
		return (paths);
	}
	else if (paths[0][0] != '\0' && !(((*arg_zero)[0] == '.' || \
		(*arg_zero)[0] == '/') && (*arg_zero)[1] != '\0'))
		return (add_new_path("/", paths));
	else
		return (paths);
}
