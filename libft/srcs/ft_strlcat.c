/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:41:42 by tlegrand          #+#    #+#             */
/*   Updated: 2022/12/25 15:39:03 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	end;
	size_t	j;

	end = 0;
	j = 0;
	while (dst[end] && end < dstsize)
		end++;
	if (end < dstsize)
	{
		while (src[j] && end + j < dstsize - 1)
		{
			dst[end + j] = src[j];
			j++;
		}
		dst[end + j] = 0;
	}
	while (src[j])
		j++;
	return (end + j);
}
