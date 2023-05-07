/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:57:21 by tlegrand          #+#    #+#             */
/*   Updated: 2022/12/25 15:39:03 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*smod;

	if (!s || !(*f))
		return (NULL);
	len = ft_strlen(s);
	smod = (char *)malloc((len + 1) * sizeof(char));
	if (!smod)
		return (NULL);
	smod[len] = 0;
	while (len > 0)
	{
		len--;
		smod[len] = (*f)(len, s[len]);
	}
	return (smod);
}
