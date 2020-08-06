/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:45:21 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/25 09:52:15 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void *ptr;

	ptr = malloc(nelem * elsize);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, nelem * elsize);
	return (ptr);
}
