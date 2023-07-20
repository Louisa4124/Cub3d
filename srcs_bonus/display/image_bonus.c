/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:39:15 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/20 22:23:36 by tlegrand         ###   ########.fr       */
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
	{
		mod = (i.y + k.y);
		if (mod < 0)
			mod = max - mod;
		else
			mod %= max;
		return (mod);
	}
	else
	{
		mod = (i.x + k.x);
		if (mod < 0)
			mod = max - mod;
		else
			mod %= max;
		return (mod);
	}
}

t_color	blur_image_avg(unsigned int *img_data, t_vec2d i, int width, int height, int half_kernel)
{
	unsigned int	pixel;
	t_vec2d			k;
	t_color			c;
	t_color			sum;

	set_color(&sum, 0, 0, 0);
	k.y = -half_kernel;

	while (k.y <= half_kernel)
	{
		k.x = -half_kernel;
		while (k.x <= half_kernel)
		{
			pixel = img_data[ft_super_mod_cycle(height, i, k, 0) * width + ft_super_mod_cycle(width, i, k, 1)];
			set_color(&c, (pixel >> 16) & 0xFF, (pixel >> 8) & 0xFF, pixel & 0xFF);
			add_color(&sum, c.r, c.g, c.b);
			++k.x;
		}
		++k.y;
	}
	return (sum);
}

void	blur_image(unsigned int *img_data, int width, int height)
{
	int				ker_size;
	int				half_ker;
	t_vec2d			i;
	t_color			sum;
	t_color			avg;

	ker_size = 25;
	half_ker = ker_size * 0.5;
	i.y = 0;
	while (i.y < height) 
	{
		i.x = 0;
		while (i.x < width) 
		{
			sum = blur_image_avg(img_data, i, width, height, half_ker);
			set_color(&avg, sum.r / (ker_size * ker_size), sum.g / \
				(ker_size * ker_size), sum.b / (ker_size * ker_size));
			img_data[i.y * width + i.x] = (avg.r << 16) | (avg.g << 8) | avg.b;
			++i.x;
		}
		++i.y;
	}
}
