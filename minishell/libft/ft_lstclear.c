/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 08:50:49 by yiwasa            #+#    #+#             */
/*   Updated: 2020/07/11 08:50:52 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *l;
	t_list *tmp;

	if (lst == NULL || del == NULL)
		return ;
	l = *lst;
	while (l != NULL)
	{
		tmp = l->next;
		ft_lstdelone(l, del);
		l = tmp;
	}
	*lst = NULL;
}
