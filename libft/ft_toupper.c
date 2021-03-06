/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:28:20 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/24 14:43:51 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_toupper(int c)
{
	int diff;

	diff = 'a' - 'A';
	if (ft_isalpha(c) && (c >= 'a' && c <= 'z'))
		return (c - diff);
	return (c);
}
