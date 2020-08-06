/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 11:58:08 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/28 11:14:34 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int srclen;
	unsigned int dstlen;
	unsigned int i;
	unsigned int k;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dest);
	if (dstlen >= size)
		return (srclen + size);
	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	k = 0;
	while (k < (size - dstlen - 1) && src[k] != '\0')
	{
		dest[i + k] = src[k];
		k++;
	}
	dest[i + k] = '\0';
	return (dstlen + srclen);
}
