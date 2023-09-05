/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:39:31 by louisa            #+#    #+#             */
/*   Updated: 2023/09/05 13:27:25 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	set_pixel(t_vec2d i, t_vec2d j, t_img src, t_img *img)
{
	int		pixel;
	int		*dst;

	pixel = *(int *)(src.addr + (i.y * src.ll + i.x * (src.bpp >> 3)));
	if (!(pixel >> 24))
	{
		dst = (int *)(img->addr + (j.y * img->ll + j.x * (img->bpp >> 3)));
		*dst = pixel;
	}
}

void	draw_on(t_img *dst, t_vec2d pos, t_img src, t_area area)
{
	t_vec2d	idx;
	t_vec2d	i_dst;

	pos.x -= area.start_x;
	pos.y -= area.start_y;
	idx.y = area.start_y - 1;
	while (++idx.y < area.end_y && idx.y < src.height)
	{
		idx.x = area.start_x - 1;
		while (++idx.x < area.end_x && idx.x < src.width)
		{
			i_dst = (t_vec2d){pos.x + idx.x, pos.y + idx.y};
			if (i_dst.x < WIDTH && i_dst.x >= 0 
				&& i_dst.y < HEIGHT && i_dst.y >= 0)
				set_pixel(idx, i_dst, src, dst);
		}
	}
}

void	ft_draw_img(t_img *dst, t_img src, int x, int y)
{
	t_vec2d	idx;
	t_vec2d	i_dst;

	idx.y = 0;
	while (idx.y < src.height)
	{
		idx.x = 0;
		while (idx.x < src.width)
		{
			i_dst = (t_vec2d){x + idx.x, y + idx.y};
			if (i_dst.x < WIDTH && i_dst.x >= 0 && i_dst.y < HEIGHT 
				&& i_dst.y >= 0)
				set_pixel(idx, i_dst, src, dst);
			++idx.x;
		}
		++idx.y;
	}
}

void	ft_draw_img_vel(t_img *img, t_img src, float x, float y)
{
	t_vec2d	i;
	t_vec2d	j;

	i.y = 0;
	while (i.y < src.height)
	{
		i.x = 0;
		while (i.x < src.width)
		{
			j = (t_vec2d){(int)(x + i.x), (int)(y + i.y)};
			if (j.x < WIDTH && j.x >= 0 && j.y < HEIGHT && j.y >= 0)
				set_pixel(i, j, src, img);
			++i.x;
		}
		++i.y;
	}
}
