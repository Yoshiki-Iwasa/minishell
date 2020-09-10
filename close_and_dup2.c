/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_dup2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:33:44 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 12:33:45 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** パイプの入り口出口のclose　と dup2 による新しい割り振りを決定。
*/

void	close_and_dup2_2(int pp_zero, int pp_one)
{
	close(pp_one);
	dup2(pp_zero, 0);
	close(pp_zero);
}

/*
** パイプの入り口出口のclose　と dup2 による新しい割り振りを決定。
*/

void	close_and_dup2_1(int pp_zero, int pp_one)
{
	close(pp_zero);
	dup2(pp_one, 1);
	close(pp_one);
}
