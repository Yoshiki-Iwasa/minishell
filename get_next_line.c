/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwasa <yiwasa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:11:34 by yiwasa            #+#    #+#             */
/*   Updated: 2020/09/11 10:24:24 by yiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		just_for_return(char **line, char **tmp)
{
	free(*line);
	free(*tmp);
	return (-1);
}

static int		end_of_file(char **line, char *s_fd)
{
	*line = ft_strdup(s_fd);
	free(s_fd);
	if (!*line)
		return (-1);
	s_fd = NULL;
	return (0);
}

static int		pattern_rv_positive(char **s, int fd, char **line, int len)
{
	char	*tmp;
	int		flag;

	flag = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\0')
		return (end_of_file(line, s[fd]));
	else
	{
		*line = ft_substr(s[fd], 0, len);
		if (!ft_strcmp(*line, "exit"))
			flag = 1;
		tmp = ft_strdup(&s[fd][len + 1]);
		free(s[fd]);
		if (!tmp || !line)
			return (just_for_return(line, &tmp));
		s[fd] = tmp;
		if (flag)
			free(s[fd]);
	}
	return (1);
}

static int		decide_return_value(char **s, int rv, int fd, char **line)
{
	int len;

	len = 0;
	if (rv == 0 && s[fd] == NULL)
	{
		write(1, "  \b\b ", 4);
		free(s[fd]);
		s[fd] = NULL;
		*line = ft_strdup("");
		if (*line == NULL)
			return (-1);
		return (0);
	}
	else if (rv < 0)
		return (-1);
	else
		return (pattern_rv_positive(s, fd, line, len));
}

int				get_next_line(int fd, char **line)
{
	char			*buf;
	static char		*s[MAX_FD];
	char			*tmp;
	int				rv;

	buf = malloc(20 + 1);
	if (fd < 0 || line == NULL || fd > MAX_FD || buf == NULL)
		return (-1);
	while ((rv = read(fd, buf, 20)) > 0)
	{
		buf[rv] = '\0';
		if (s[fd] == NULL)
			tmp = ft_strdup(buf);
		else
			tmp = ft_strjoin(s[fd], buf);
		free(s[fd]);
		if (!tmp)
			return (-1);
		s[fd] = tmp;
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	free(buf);
	return (decide_return_value(s, rv, fd, line));
}
