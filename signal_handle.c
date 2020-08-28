/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 09:35:24 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/26 08:26:54 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	シグナルの条件を一つの関数にまとめる
*/

void	setting_signal(void)
{
	signal(SIGINT, sig_handle_C);
	signal(SIGQUIT, sig_handle_bs);
}
