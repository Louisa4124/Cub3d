/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:14 by tlegrand          #+#    #+#             */
/*   Updated: 2023/01/20 20:09:38 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_fill_buff(char **s_buff, int fd)
{
	char	read_buff[BUFFER_SIZE + 1];
	int		len;

	while (!ft_strchr(*s_buff, '\n'))
	{
		len = read(fd, read_buff, BUFFER_SIZE);
		if (len == -1)
		{
			free(*s_buff);
			*s_buff = NULL;
			return (1);
		}
		if (!len)
			break ;
		read_buff[len] = '\0';
		*s_buff = ft_self_append(*s_buff, read_buff);
		if (!*s_buff)
			return (1);
		if (!len)
			break ;
	}
	return (0);
}

static char	*get_line(char *s_buff)
{
	char	*line;
	size_t	i;

	if (!s_buff || !*s_buff)
		return (NULL);
	i = 0;
	while (s_buff[i] && s_buff[i] != '\n')
		i++;
	if (s_buff[i] == '\n')
		i++;
	line = ft_substr(s_buff, 0, i);
	return (line);
}

static char	*get_stock(char *s_buff)
{
	size_t	i;
	char	*new;

	if (!s_buff)
		return (NULL);
	i = 0;
	while (s_buff[i] && s_buff[i] != '\n')
		i++;
	if (!s_buff[i])
	{
		free(s_buff);
		return (NULL);
	}
	if (s_buff[i] == '\n')
		i++;
	new = ft_substr(s_buff, i, ft_strlen(s_buff) - i);
	free(s_buff);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*s_buff[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (NULL);
	if (ft_fill_buff(&s_buff[fd], fd))
		return (NULL);
	line = get_line(s_buff[fd]);
	if (!line)
	{
		if (s_buff[fd])
			free(s_buff[fd]);
		s_buff[fd] = NULL;
		return (NULL);
	}
	s_buff[fd] = get_stock(s_buff[fd]);
	return (line);
}
