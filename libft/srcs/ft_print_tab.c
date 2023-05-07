/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:26:20 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/30 18:30:14 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_tab2d_char(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ((void) ft_putstr_fd("tab NULL\n", 2));
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		i++;
	}
}

void	ft_print_tab_int(int *tab, int size)
{
	int	i;

	i = 0;
	if (!tab)
		return ((void) ft_putstr_fd("tab NULL\n", 2));
	while (i < size)
	{
		ft_putnbr_fd(tab[i], 1);
		i++;
	}
}
