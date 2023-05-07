/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multijoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:21:08 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/20 15:25:33 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_len_arg(int n, va_list ap)
{
	char	*buff;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (i < n)
	{
		buff = va_arg(ap, char *);
		len += ft_strlen2(buff);
		i++;
	}
	return (len);
}

char	*ft_multijoin(int n, ...)
{
	va_list	ap;
	char	*buff;
	char	*join;
	int		len;

	len = 0;
	va_start(ap, n);
	join = ft_calloc(ft_len_arg(n, ap) + 1, sizeof(char));
	va_end(ap);
	va_start(ap, n);
	while (n > 0)
	{
		buff = va_arg(ap, char *);
		if (buff)
			ft_strlcpy(join + len, buff, ft_strlen2(buff) + 1);
		len += ft_strlen2(buff);
		n--;
	}
	va_end(ap);
	return (join);
}
