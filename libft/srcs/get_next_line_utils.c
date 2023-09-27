/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:40:09 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/27 22:50:20 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*gnl_chr_nl(char *s)
{
	if (!s)
		return (NULL);
	while (*s != '\n' && *s)
		++s;
	if (*s == '\n')
		return (s);
	return (NULL);
}

size_t	gnl_strlcat(char *dst, char *src, size_t start, size_t size)
{
	size_t	j;

	j = 0;
	while (src && src[j] && src[j] != '\n' && start + j < size)
	{
		dst[start + j] = src[j];
		++j;
	}
	if (src && src[j] == '\n')
	{
		dst[start + j] = src[j];
		++j;
	}
	dst[start + j] = '\0';
	return (start + j);
}

char	*gnl_refresh(char *s_buff)
{
	char	*ptr;
	int		len;

	ptr = gnl_chr_nl(s_buff);
	if (ptr)
		ptr++;
	len = 0;
	while (ptr && *ptr && len < BUFFER_SIZE)
	{
		*(s_buff + len) = *ptr;
		len++;
		ptr++;
	}
	while (len < BUFFER_SIZE)
	{
		*(s_buff + len) = 0;
		len++;
	}
	return (s_buff);
}

char	*gnl_expand(char *line, size_t *size)
{
	char	*new_line;

	*size = *size << 1;
	new_line = malloc((*size + 1) * sizeof(char));
	if (!new_line)
		return (free(line), NULL);
	gnl_strlcat(new_line, line, 0, *size);
	if (line)
		free(line);
	return (new_line);
}

char	*gnl_init(size_t *idx, size_t *size, int *n_read)
{
	*idx = 0;
	*size = BUFFER_SIZE;
	*n_read = 1;
	return (NULL);
}
