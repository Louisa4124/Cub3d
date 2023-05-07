/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_extract_number.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:05:14 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/06 22:04:02 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int							write_buffer(t_print_buffer *p, char c);
int							padding(t_print_buffer *p, char c, int size);
unsigned long long int		ft_power_recursive(unsigned long long int nb, \
	int power);

static int	get_base(int flag)
{
	if (flag == 'b')
		return (2);
	if (flag == 'o')
		return (8);
	if (flag == 'd' || flag == 'i' || flag == 'u')
		return (10);
	if (flag == 'x' || flag == 'X' || flag == 'p')
		return (16);
	return (-1);
}

int	ft_numlen(unsigned long long int num, int base)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num)
	{
		num /= base;
		++len;
	}
	return (len);
}

int	extract_number(t_print_buffer *p, unsigned long int number, \
	int size, int flags[4])
{
	unsigned long long int	pow;
	char					*base;
	int						w_len;
	int						base_len;

	w_len = 0;
	base_len = get_base(flags[3]);
	if (flags[3] == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (flags[0] & PRECISION)
		w_len += padding(p, '0', flags[2] - size);
	pow = ft_power_recursive(base_len, size - 1);
	if ((flags[0] & PRECISION) && flags[2] == 0 && number / pow == 0)
		return (w_len);
	while (pow)
	{
		w_len += write_buffer(p, base[(number / pow)]);
		number = number - ((number / pow) * pow);
		pow /= base_len;
	}
	return (w_len);
}
