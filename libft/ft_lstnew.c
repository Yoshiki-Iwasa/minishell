/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:36:54 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/24 08:12:43 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new_element;

	new_element = malloc(sizeof(t_list));
	if (new_element == NULL)
		return (0);
	new_element->content = ft_strdup(content);
	if (!new_element->content)
	{
		free(new_element);
		return (0);
	}
	new_element->next = NULL;
	return (new_element);
}
