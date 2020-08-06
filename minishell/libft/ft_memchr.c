/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:29:53 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/25 09:52:51 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *bigptr, int ch, size_t len)
{
	const char	*big;
	size_t		n;

	big = (const char*)bigptr;
	n = 0;
	while (n < len)
	{
		if (big[n] == ch)
			return (void*)&big[n];
		n++;
	}
	return (0);
}
