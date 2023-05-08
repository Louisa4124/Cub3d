/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:14 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/08 21:16:35 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*gnl_chr_nl(char *s);
size_t	gnl_strlcat(char *dst, char *src, size_t start);
char	*gnl_refresh(char *s_buff);
char	*gnl_expand(char *line, size_t *size);
char	*gnl_init(size_t *idx, size_t *size, int *n_read);

int	get_next_line(int fd, char **line)
{
	static char	s_buff[MAX_FD][BUFFER_SIZE + 1];
	size_t		idx;
	size_t		size;
	int			n_read;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > MAX_FD)
		return (1);
	*line = gnl_init(&idx, &size, &n_read);
	while (!gnl_chr_nl(*line))
	{
		if (s_buff[fd][0] == 0)
			n_read = read(fd, s_buff[fd], BUFFER_SIZE);
		if (n_read == -1)
			return (free(*line), 1);
		else if (n_read == 0)
			return (0);
		if (idx == size - 1)
			*line = gnl_expand(*line, &size);
		if (!*line)
			return (1);
		idx = gnl_strlcat(*line, s_buff[fd], idx);
		gnl_refresh(s_buff[fd]);
	}
	return (0);
}
