/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:20:45 by yiwasa            #+#    #+#             */
/*   Updated: 2020/08/07 10:59:02 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	s1_letter;
	unsigned char	s2_letter;

	if (s1 == NULL || s2 == NULL)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	s1_letter = (unsigned char)s1[i];
	s2_letter = (unsigned char)s2[i];
	return (s1_letter - s2_letter);
}


char	*ft_strcat(char *dest, char *src)
{
  int d_length;
  int i;

  d_length = -1;
  while (dest[++d_length]);

  i = 0;
  while (src[i])
  {
    dest[d_length] = src[i];
    i++;
    d_length++;
  }
  dest[d_length] = '\0';

  return (dest);
}


void	ft_putendl(void *str)
{
	if (str == 0)
		return ;
	ft_putendl_fd((char*)str, 1);
}


/*
	空白を判定する
*/

int		ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
