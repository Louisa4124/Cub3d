/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:24:44 by tlegrand          #+#    #+#             */
/*   Updated: 2022/12/25 15:39:03 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_sizen(int n)
{
	int		size;

	if (!n)
		return (1);
	size = 0;
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static void	ft_fill(char *str, int n, int size, int i)
{
	while (size >= i)
	{
		str[size] = (n % 10) + 48;
		n = n / 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	int		i;
	char	*str;

	i = 0;
	if (n == -2147483648)
	{
		str = ft_substr("-2147483648", 0, 11);
		return (str);
	}
	if (n < 0)
	{
		i++;
		n = -n;
	}
	size = ft_sizen(n);
	str = (char *)malloc((size + 1 + i) * sizeof(char));
	if (!str)
		return (NULL);
	str[size + i] = 0;
	if (i == 1)
		str[0] = '-';
	size += i - 1;
	ft_fill(str, n, size, i);
	return (str);
}
