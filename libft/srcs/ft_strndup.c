/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:19:01 by lboudjem          #+#    #+#             */
/*   Updated: 2023/03/30 19:27:01 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(char *src, int n)
{
	int		tmp;
	char	*cpy;

	cpy = (char *)ft_calloc((n + 1), sizeof(char));
	if (!cpy)
		return (NULL);
	tmp = 0;
	while (src && src[tmp] && tmp < n)
	{
		cpy[tmp] = src[tmp];
		tmp++;
	}
	return (cpy);
}
