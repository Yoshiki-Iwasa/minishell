/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:55:06 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/25 14:00:45 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int ch)
{
	char c;

	c = ch;
	while (*s)
	{
		if (*s == c)
			return ((char*)s);
		if (*s == '\0')
			return (NULL);
		s++;
	}
	if (c == '\0')
		return ((char*)s);
	return (NULL);
}
