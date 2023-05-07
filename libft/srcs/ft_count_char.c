/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:07:52 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/30 18:45:21 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_count_char(char *str, char c)
{
	int	n;

	n = 0;
	while (*str)
	{
		if (*str == c)
			n++;
		str++;
	}
	return (n);
}

int	ft_count_charset(char *str, char *charset)
{
	int	n;

	n = 0;
	while (*str)
	{
		if (ft_strchr(charset, *str))
			n++;
		str++;
	}
	return (n);
}
