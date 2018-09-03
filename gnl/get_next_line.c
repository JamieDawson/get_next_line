/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:06:34 by jadawson          #+#    #+#             */
/*   Updated: 2018/04/19 23:30:36 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*connect(char *str, char *buf)
{
	char *strptr;

	strptr = ft_strjoin(str, buf);
	free(str);
	return (strptr);
}

int		the_end(char **line, char **strings, char **holder)
{
	if (ft_strlen(strings[0]) != 0)
	{
		*line = strings[0];
		free(*holder);
		*holder = ft_strnew(0);
		return (1);
	}
	free(*holder);
	*holder = NULL;
	return (0);
}

int		looping(int fd, char **strings, char **holder, char **line)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];

	while (1)
	{
		ret = read(fd, &buf, BUFF_SIZE);
		if (ret < 0)
			return (-1);
		if (ret == 0)
			return (the_end(line, strings, holder));
		buf[ret] = '\0';
		strings[1] = ft_strchr(buf, '\n');
		if (strings[1] != NULL)
		{
			*strings[1] = '\0';
			strings[0] = connect(strings[0], buf);
			*strings[1] = '\n';
			*holder = connect(*holder, strings[1] + 1);
			*line = strings[0];
			return (1);
		}
		strings[0] = connect(strings[0], buf);
	}
}

int		get_next_line(const int fd, char **line)
{
	char		*strings[3];
	static char	*holder = NULL;

	strings[0] = ft_strnew(0);
	if (holder == NULL)
		holder = ft_strnew(0);
	if (fd < 0 || !line || BUFF_SIZE < 0)
		return (-1);
	strings[1] = ft_strchr(holder, '\n');
	if (strings[1] != NULL)
	{
		*strings[1] = '\0';
		*line = ft_strdup(holder);
		*strings[1] = '\n';
		strings[2] = ft_strdup(strings[1] + 1);
		free(holder);
		holder = strings[2];
		return (1);
	}
	strings[0] = connect(strings[0], holder);
	free(holder);
	holder = ft_strnew(0);
	return (looping(fd, strings, &holder, line));
}
