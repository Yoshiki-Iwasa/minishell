/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:02:09 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/30 12:03:07 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strdup(const char *src)
{
	char	*p;
	int		len;
	int		i;

	len = ft_strlen(src);
	p = (char*)malloc(len + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*newstr;
	size_t	i;
	size_t	j;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = malloc((s1len + s2len + 1) * sizeof(char));
	if (newstr == 0)
		return (0);
	i = 0;
	while (i < s1len)
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2len)
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	size_t	size;
	char	*tab;

	count = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	if (!(tab = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (count < len)
	{
		tab[count] = s[start + count];
		count++;
	}
	tab[count] = '\0';
	return (tab);
}

size_t		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (*(str + i) != '\0')
	{
		++i;
	}
	return (i);
}

char		*ft_strchr(const char *s, int ch)
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
