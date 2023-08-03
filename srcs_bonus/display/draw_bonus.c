/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:44 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/03 22:21:38 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp >> 3));
	*(unsigned int *) dst = color;
}

void	ft_mlx_pixel_put2(t_img *img, int x, int y, int color)
{
	((int *)img->addr)[y * (img->ll >> 2) + x] = color;
}

void	draw_circle(t_img *img, t_vec2d center, int rayon, int color)
{
	int	x;
	int	y;

	y = center.y - rayon;
	while (y < center.y + rayon)
	{
		x = center.x - rayon;
		while (x < center.x + rayon)
		{
			if ((x - center.x) + (y - center.y) == rayon)
				ft_mlx_pixel_put(img, center.x, center.y, color);
			++x;
		}
		++y;
	}
}

void	draw_square(t_img *img, t_vec2d pos, int size, int color)
{
	int	max_y;
	int	max_x;
	int	tmp;

	max_y = pos.y + size;
	max_x = pos.x + size;
	tmp = pos.x;
	while (pos.y < max_y)
	{
		pos.x = tmp;
		while (pos.x < max_x)
		{
			ft_mlx_pixel_put(img, pos.x, pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}
