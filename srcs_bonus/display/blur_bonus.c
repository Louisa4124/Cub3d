/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:39:15 by lboudjem          #+#    #+#             */
/*   Updated: 2023/09/18 21:24:45 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	add_color(t_color *c, int v1, int v2, int v3)
{
	c->r += v1;
	c->g += v2;
	c->b += v3;
}

int	mod_cycle(int max, t_vec2d i, t_vec2d k, int axis)
{
	int	mod;

	if (axis == 0)
		mod = (i.y + k.y);
	else
		mod = (i.x + k.x);
	if (mod < 0)
		mod = max - mod;
	else if (mod > max)
		mod %= max;
	return (mod);
}

int	limit(int max, t_vec2d i, t_vec2d k, int axis)
{
	int	limit;

	if (axis == 0)
		limit = (i.y + k.y);
	else
		limit = (i.x + k.x);
	if (limit < 0)
		limit = 0;
	else if (limit > max)
		limit = max;
	return (limit);
}

t_color	blur_image_avg(t_img *img, unsigned int *img_data, t_vec2d i, \
	int kernel[2])
{
	unsigned int	pixel;
	t_vec2d			k;
	t_color			avg;

	avg = (t_color){0, 0, 0};
	k.y = -kernel[0];
	while (k.y <= kernel[0])
	{
		k.x = -kernel[0];
		while (k.x <= kernel[0])
		{
			pixel = img_data[limit(img->height, i, k, 0) * \
				img->width + limit(img->width, i, k, 1)];
			add_color(&avg, (pixel >> 16) & 0xFF, (pixel >> 8) & 0xFF, \
				pixel & 0xFF);
			++k.x;
		}
		++k.y;
	}
	avg.r = avg.r / kernel[1];
	avg.g = avg.g / kernel[1];
	avg.b = avg.b / kernel[1];
	return (avg);
}

void	blur_image(void *ptr, void *area)
{
	unsigned int	*img_data;
	int				kernel[2];
	t_tmp			data;
	t_vec2d			i;
	t_color			avg;

	kernel[0] = BLUR * 0.5;
	kernel[1] = BLUR * BLUR;
	data.img = ptr;
	data.area = area;
	img_data = (unsigned int *)data.img->addr;
	i.y = data.area->start_y;
	while (i.y < data.area->end_y)
	{
		i.x = data.area->start_x;
		while (i.x < data.area->end_x)
		{
			avg = blur_image_avg(data.img, img_data, i, kernel);
			img_data[i.y * data.img->width + i.x] = \
				(avg.r << 16) | (avg.g << 8) | avg.b;
			++i.x;
		}
		++i.y;
	}
}
