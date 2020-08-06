/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:09:45 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/25 14:17:42 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *cp, int ch)
{
	char *save;
	char c;

	c = ch;
	save = (char*)0;
	while (1)
	{
		if (*cp == ch)
			save = (char*)cp;
		if (*cp == '\0')
			return (save);
		cp++;
	}
	return (save);
}
