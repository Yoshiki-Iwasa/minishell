/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:32:46 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/24 14:35:08 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
