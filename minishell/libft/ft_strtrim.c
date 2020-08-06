/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:41:50 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/26 09:11:22 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_tail(char const *s1, char const *set)
{
	size_t	s1len;
	int		exist;
	size_t	count;
	size_t	i;

	s1len = ft_strlen(s1);
	count = 0;
	while (1)
	{
		exist = 0;
		i = 0;
		while (set[i] != '\0')
		{
			if (s1[s1len - 1] == set[i++])
			{
				count++;
				exist = 1;
			}
		}
		if (exist)
			s1len--;
		else
			break ;
	}
	return (count);
}

void	check_head(char const **s1, char const *set)
{
	int		exist;
	size_t	i;

	while (1)
	{
		exist = 0;
		i = 0;
		while (set[i] != '\0')
		{
			if (**s1 == set[i])
			{
				exist = 1;
				break ;
			}
			i++;
		}
		if (exist)
			(*s1)++;
		else
			break ;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	lensub;
	size_t	count;
	size_t	i;

	count = check_tail(s1, set);
	if (count == ft_strlen(s1))
		return (ft_strdup(""));
	check_head(&s1, set);
	lensub = ft_strlen(s1) - count;
	newstr = malloc(lensub + 1);
	if (newstr == 0)
		return (0);
	i = 0;
	while (i < (lensub))
	{
		newstr[i] = *s1++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
