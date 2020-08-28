/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:07:07 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/29 08:20:07 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	substr = malloc((len + 1) * sizeof(char));
	if (substr == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		if (s[start + i] == '\0')
			break ;
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
