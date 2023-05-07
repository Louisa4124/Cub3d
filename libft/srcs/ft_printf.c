/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:05:47 by tlegrand          #+#    #+#             */
/*   Updated: 2023/01/22 16:40:51 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_select_print(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (c == 'd' || c == 'i' || c == 'u')
		return (ft_putnbr_base(va_arg(ap, int), "0123456789"));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(ap, int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(ap, int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		n;
	char	*idset;
	char	*format;
	va_list	ap;

	idset = "cspdiuxX";
	va_start(ap, str);
	n = 0;
	while (*str)
	{
		format = ft_strchr(idset, (int)*(str + 1));
		if (*str == '%')
		{
			str++;
			if (format != NULL)
				n += ft_select_print(*format, ap);
			else
				n += ft_putchar(*str);
		}
		else
			n += ft_putchar(*str);
		str++;
	}
	va_end(ap);
	return (n);
}
