/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:35:14 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/06 22:05:28 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	write_buffer(t_print_buffer *p, char c);

int	padding(t_print_buffer *p, char c, int size)
{
	int	w_len;

	w_len = 0;
	while (size-- > 0)
		w_len += write_buffer(p, c);
	return (w_len);
}

static int	write_sign(t_print_buffer *p, int sign, int specifier)
{
	int	w_len;

	w_len = 0;
	if (sign != -1)
		w_len += write_buffer(p, sign);
	if (sign == '0' && (specifier == 'x' || specifier == 'p'))
		w_len += write_buffer(p, 'x');
	else if (sign == '0' && specifier == 'X')
		w_len += write_buffer(p, 'X');
	else if (sign == '0' && specifier == 'b')
		w_len += write_buffer(p, 'b');
	return (w_len);
}

int	pad_adjust_right(t_print_buffer *p, int size, int sign, int flags[4])
{
	int	w_len;

	w_len = 0;
	if (sign != -1)
		--flags[1];
	if (sign == '0' && flags[3] != 'o')
		--flags[1];
	if ((flags[0] & LEFT) == 0 && flags[1] > size)
	{
		if ((flags[0] & PRECISION) == 0 && (flags[0] & ZERO))
		{
			w_len += write_sign(p, sign, flags[3]);
			w_len += padding(p, '0', flags[1] - size);
		}
		else
		{
			w_len += padding(p, ' ', flags[1] - size);
			w_len += write_sign(p, sign, flags[3]);
		}
	}
	else
		w_len += write_sign(p, sign, flags[3]);
	return (w_len);
}

int	pad_adjust_left(t_print_buffer *p, int size, int flags[4])
{
	int	w_len;

	w_len = 0;
	if ((flags[0] & LEFT) && flags[1] > size)
		w_len += padding(p, ' ', flags[1] - size);
	return (w_len);
}
