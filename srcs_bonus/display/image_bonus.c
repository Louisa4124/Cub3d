/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:39:31 by louisa            #+#    #+#             */
/*   Updated: 2023/09/05 00:01:22 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	draw_on(t_img *img_dst, t_vec2d pos, t_img img_src, t_area area)
{
	char	*dst;
	char	*src;
	int		i;
	int		j;

	pos.x -= area.start_x;
	pos.y -= area.start_y;
	i = area.start_y - 1;
	while (++i < area.end_y && i < img_src.height)
	{
		j = area.start_x - 1;
		while (++j < area.end_x && j < img_src.width)
		{
			if ((pos.x + j) < WIDTH && (pos.x + j) >= 0 
				&& (pos.y + i) < HEIGHT && (pos.y + i) >= 0)
			{
				dst = (img_dst->addr + ((pos.y + i) * img_dst->ll + (pos.x + j) \
					*(img_dst->bpp >> 3)));
				src = (img_src.addr + (i * img_src.ll + j *(img_src.bpp >> 3)));
				if (*(unsigned int *)src != 0xff000000)
					*(unsigned int *)dst = *(unsigned int *)src;
			}
		}
	}
}

void	ft_draw_img(t_img *img_dst, t_img tex, int x, int y)
{
	char	*dst;
	char	*src;
	int		i;
	int		j;

	i = 0;
	while (i < tex.height)
	{
		j = 0;
		while (j < tex.width)
		{
			if ((x + j) < WIDTH && (x + j) >= 0 && (y + i) < HEIGHT 
				&& (y + i) >= 0)
			{
				dst = (img_dst->addr + ((y + i) * img_dst->ll + (x + j)
							*(img_dst->bpp >> 3)));
				src = (tex.addr + (i * tex.ll + j
							*(tex.bpp >> 3)));
				if (*(unsigned int *)src != 0xff000000)
					*(unsigned int *)dst = *(unsigned int *)src;
			}
			++j;
		}
		++i;
	}
}

void	ft_draw_img_vel(t_img *img, t_img tex, float x, float y)
{
	char	*dst;
	char	*src;
	t_vec2d	i;
	t_vec2d	j;

	i.x = 0;
	while (i.x < tex.height)
	{
		i.y = 0;
		while (i.y < tex.width)
		{
			j.x = (int)(x + i.y);
			j.y = (int)(y + i.x);
			if (j.x < WIDTH && j.x >= 0 && j.y < HEIGHT && j.y >= 0)
			{
				dst = (img->addr + (j.y * img->ll + j.x * (img->bpp >> 3)));
				src = (tex.addr + (i.x * tex.ll + i.y * (tex.bpp >> 3)));
				if (*(unsigned int *)src != 0xff000000)
					*(unsigned int *)dst = *(unsigned int *)src;
			}
			++i.y;
		}
		++i.x;
	}
}
