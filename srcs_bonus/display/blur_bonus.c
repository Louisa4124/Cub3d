/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:39:15 by lboudjem          #+#    #+#             */
/*   Updated: 2023/09/21 12:47:07 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	add_color(t_color *c, int v1, int v2, int v3)
{
	c->r += v1;
	c->g += v2;
	c->b += v3;
}

int	limit(int data[2], t_vec2d i, t_vec2d k, int axis)
{
	int	limit;

	if (axis == 0)
		limit = (i.y + k.y);
	else
		limit = (i.x + k.x);
	if (limit < data[0])
		limit = data[0];
	else if (limit >= data[1])
		limit = data[1] - 1;
	return (limit);
}

t_color	blur_image_avg(t_img *img, unsigned int *img_data, t_vec2d i, \
	t_area *max)
{
	int				kernel[2];
	unsigned int	pixel;
	t_vec2d			k;
	t_color			avg;

	avg = (t_color){0, 0, 0};
	kernel[0] = BLUR * 0.5;
	kernel[1] = BLUR * BLUR;
	k.y = -kernel[0] + 1;
	while (k.y <= kernel[0] && k.y < max->end_y)
	{
		k.x = -kernel[0] + 1;
		while (k.x <= kernel[0] && k.x < max->end_x)
		{
			pixel = img_data[limit((int [2]){max->start_y, max->end_y}, i, k, \
				0) * img->width + limit((int [2]){max->start_x, max->end_x}, \
				i, k, 1)];
			add_color(&avg, (pixel >> 16) & 0xFF, (pixel >> 8) & 0xFF, \
				pixel & 0xFF);
			++k.x;
		}
		++k.y;
	}
	avg = (t_color){avg.r / kernel[1], avg.g / kernel[1], avg.b / kernel[1]};
	return (avg);
}

void	blur_image(void *ptr, void *area)
{
	unsigned int	*img_data;
	t_tmp			data;
	t_vec2d			i;
	t_color			avg;

	data.img = ptr;
	data.area = area;
	img_data = (unsigned int *)data.img->addr;
	i.y = data.area->start_y;
	while (i.y < data.area->end_y)
	{
		i.x = data.area->start_x;
		while (i.x < data.area->end_x)
		{
			avg = blur_image_avg(data.img, img_data, i, data.area);
			img_data[i.y * data.img->width + i.x] = \
				(avg.r << 16) | (avg.g << 8) | avg.b;
			++i.x;
		}
		++i.y;
	}
}
