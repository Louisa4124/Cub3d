/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:39:15 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/21 19:59:10 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	set_color(t_color *c, int v1, int v2, int v3)
{
	c->r = v1;
	c->g = v2;
	c->b = v3;
}

void	add_color(t_color *c, int v1, int v2, int v3)
{
	c->r += v1;
	c->g += v2;
	c->b += v3;
}

int	ft_super_mod_cycle(int max, t_vec2d i, t_vec2d k, int axis)
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

t_color	blur_image_avg(t_img *img, unsigned int *img_data, t_vec2d i, \
	int kernel[2])
{
	unsigned int	pixel;
	t_vec2d			k;
	t_color			c;
	t_color			avg;

	set_color(&avg, 0, 0, 0);
	k.y = -kernel[0];
	while (k.y <= kernel[0])
	{
		k.x = -kernel[0];
		while (k.x <= kernel[0])
		{
			pixel = img_data[ft_super_mod_cycle(img->height, i, k, 0) * \
				img->width + ft_super_mod_cycle(img->width, i, k, 1)];
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

void	blur_image(t_img *img, unsigned int *img_data)
{
	int		kernel[2];
	t_vec2d	i;
	t_color	avg;

	kernel[0] = BLUR * 0.5;
	kernel[1] = BLUR * BLUR;
	i.y = 0;
	while (i.y < img->height) 
	{
		i.x = 0;
		while (i.x < img->width) 
		{
			avg = blur_image_avg(img, img_data, i, kernel);
			img_data[i.y * img->width + i.x] = \
				(avg.r << 16) | (avg.g << 8) | avg.b;
			++i.x;
		}
		++i.y;
	}
}
