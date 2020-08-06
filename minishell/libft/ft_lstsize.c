/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:46:26 by yiwasa            #+#    #+#             */
/*   Updated: 2020/06/28 14:32:20 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*forward;

	if (lst == 0)
		return (0);
	len = 1;
	forward = lst->next;
	while (forward)
	{
		forward = forward->next;
		len++;
	}
	return (len);
}
