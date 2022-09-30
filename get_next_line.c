/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 15:54:49 by kferterb          #+#    #+#             */
/*   Updated: 2021/10/28 18:26:48 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*ft_read(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*str;
	ssize_t	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
		return (NULL);
	buffer[bytes] = '\0';
	str = ft_strdup(buffer);
	return (str);
}

static char	*disconnect(char **s_res)
{
	char	*str;
	char	*point;
	char	*tmp;

	if (ft_strlen(*s_res) == 0)
	{
		free(*s_res);
		*s_res = NULL;
		return (NULL);
	}
	point = ft_strchr(*s_res, '\n');
	if (point == 0)
	{
		str = ft_strdup(*s_res);
		free(*s_res);
		*s_res = NULL;
		return (str);
	}
	*point = '\0';
	str = ft_strjoin(*s_res, "\n");
	point++;
	tmp = *s_res;
	*s_res = ft_strdup(point);
	free(tmp);
	return (str);
}

static void	connect(char **s_res, int fd)
{
	char	*tmp;
	char	*str;

	while (ft_strchr(*s_res, '\n') == 0)
	{
		str = ft_read(fd);
		tmp = *s_res;
		if (str == 0)
			break ;
		else
			*s_res = ft_strjoin(*s_res, str);
		free(tmp);
		free(str);
	}
}

char	*get_next_line(int fd)
{
	static char	*s_res;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (s_res == 0)
	{
		s_res = ft_read(fd);
		if (s_res == 0)
			return (NULL);
	}
	connect(&s_res, fd);
	res = disconnect(&s_res);
	return (res);
}
