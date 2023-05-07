/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:59:15 by tlegrand          #+#    #+#             */
/*   Updated: 2022/12/25 15:47:09 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr(char *s)
{
	int	n;

	n = 0;
	if (!s)
	{
		n += ft_putstr("(null)");
		return (n);
	}
	while (*s)
	{
		n += ft_putchar(*s);
		s++;
	}
	return (n);
}
