/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:34:54 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/06 22:11:08 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

unsigned long long int	ft_power_recursive(unsigned long long int nb, int power)
{
	unsigned long long int		res;

	res = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (res);
	if (power > 1)
		res *= ft_power_recursive(nb, power - 1);
	res *= nb;
	return (res);
}

int	is_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i')
		return (1);
	if (c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == '%' || c == 'b')
		return (1);
	return (0);
}

int	is_flag(char c)
{
	if (c == '-')
		return (LEFT);
	if (c == '0')
		return (ZERO);
	if (c == ' ')
		return (BLANK);
	if (c == '+')
		return (PLUS);
	if (c == '#')
		return (ALTERNATE);
	return (0);
}
