/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 09:35:24 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/10 10:14:55 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** シグナルの条件を一つの関数にまとめる
*/

void	setting_signal(void)
{
	signal(SIGINT, sig_handle_c);
	signal(SIGQUIT, sig_handle_bs);
}
