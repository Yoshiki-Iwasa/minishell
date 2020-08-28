/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:39:08 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/24 14:36:23 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t littlelen;

	if (*little == '\0')
		return ((char*)big);
	littlelen = ft_strlen(little);
	while (*big != '\0' && len-- >= littlelen)
		if (ft_memcmp(big, little, littlelen) == 0)
			return ((char*)big);
		else
			big++;
	return (0);
}
