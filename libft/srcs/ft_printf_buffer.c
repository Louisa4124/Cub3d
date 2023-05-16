/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:13:55 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/16 11:06:39 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	flush_buffer(t_print_buffer *p)
{
	int	w_len;

	w_len = 0;
	if (p->idx)
		w_len = write(1, p->buffer, p->idx);
	p->idx = 0;
	return (w_len);
}

int	write_buffer(t_print_buffer *p, char c)
{
	int	w_len;

	w_len = 0;
	p->buffer[p->idx] = c;
	++p->idx;
	if (p->idx == P_BUFFER_SIZE)
		w_len += flush_buffer(p);
	return (w_len);
}

int	write_buffer_str(t_print_buffer *p, char *str, int max)
{
	int	w_len;

	w_len = 0;
	if (max < 0)
	{
		while (*str)
		{
			w_len += write_buffer(p, *str);
			++str;
		}
		return (w_len);
	}
	while (*str && max > 0)
	{
		w_len += write_buffer(p, *str);
		++str;
		--max;
	}
	return (w_len);
}
