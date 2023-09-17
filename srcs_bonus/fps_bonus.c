/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:45:36 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/17 16:00:21 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

unsigned int	get_time(void)
{
	static struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putstr_fd("Error in gettime\n", 2);
		return (-1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_printf_fps(int mode)
{
	static int	n_frame;
	static int	time;

	if (mode == -1)
		return ;
	if (get_time() - time < 1000)
		n_frame++;
	else
	{
		if (mode == 0)
			ft_printf("\r\033[2K%d", n_frame);
		else
			ft_printf("%d\n", n_frame);
		time = get_time();
		n_frame = 0;
	}
}

int	ft_get_fps(void)
{
	static int	n_frame;
	static int	time;

	if (get_time() - time < 1000)
		n_frame++;
	else
	{
		time = get_time();
		n_frame = 0;
	}
	return (n_frame);
}
