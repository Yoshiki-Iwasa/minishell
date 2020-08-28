/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:34:08 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/05 15:36:38 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**rec(char const *s, char c, int i)
{
	char const	*ptr;
	char		**container;

	while (*s == c)
		s++;
	if (!*s)
	{
		if (!(container = malloc((i + 1) * sizeof(char *))))
			return (NULL);
		container[i] = NULL;
		return (container);
	}
	ptr = s;
	while (*s && *s != c)
		s++;
	if (!(ptr = ft_substr(ptr, 0, s - ptr)))
		return (NULL);
	if (!(container = rec(s, c, i + 1)))
	{
		free((void *)ptr);
		return (NULL);
	}
	container[i] = (char *)ptr;
	return (container);
}

char		**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (rec(s, c, 0));
}
