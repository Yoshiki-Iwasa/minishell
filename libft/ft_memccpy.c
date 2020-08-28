/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:49:05 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/25 09:52:35 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dp;
	const unsigned char *sp;
	unsigned char		uc;

	if (n)
	{
		dp = dest;
		sp = src;
		uc = c;
		while (n-- != 0)
		{
			if ((*dp++ = *sp++) == uc)
				return (dp);
		}
	}
	return (0);
}
