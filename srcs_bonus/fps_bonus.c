/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:45:36 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/20 11:47:28 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_printf_fps(int mode)
{
	static int	n_frame;
	static int	time;

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
