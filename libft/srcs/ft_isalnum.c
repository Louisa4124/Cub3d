/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:55:00 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/30 18:43:28 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1)
		return (1);
	if (ft_isdigit(c) == 1)
		return (1);
	return (0);
}

int	ft_str_isalnum(char *str)
{
	while (*str && ft_isalnum(*str))
		str++;
	if (*str)
		return (0);
	return (1);
}
