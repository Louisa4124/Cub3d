/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:39:15 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/19 14:44:46 by lboudjem         ###   ########.fr       */
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

void	blur_image(unsigned int *image_data, int width, int height)
{
	unsigned int	*temp_data;
	unsigned int	pixel;
	int				kernel_size;
	int				half_kernel;
	t_vec2d			i;
	t_vec2d			k;
	t_color			sum;
	t_color			avg;
	t_color			c;
	
	temp_data = malloc(width * height * sizeof(unsigned int));
	ft_memcpy(temp_data, image_data, width * height * sizeof(unsigned int));
	kernel_size = 25;
	half_kernel = kernel_size * 0.5;
	i.y = half_kernel;
	while (i.y < height) 
	{
		i.x = half_kernel;
		while (i.x < width) 
		{
			set_color(&sum, 0, 0, 0);
			k.y = -half_kernel;
			while (k.y <= half_kernel)
			{
				k.x = -half_kernel;
				while (k.x <= half_kernel)
				{
					pixel = temp_data[(i.y + k.y) * width + (i.x + k.x)];
					set_color(&c, (pixel >> 16) & 0xFF, (pixel >> 8) & 0xFF, pixel & 0xFF);
					add_color(&sum, c.r, c.g, c.b);
					++k.x;
				}
				++k.y;
			}
			set_color(&avg, sum.r / (kernel_size * kernel_size), sum.g / \
				(kernel_size * kernel_size), sum.b / (kernel_size * kernel_size));
			image_data[i.y * width + i.x] = (avg.r << 16) | (avg.g << 8) | avg.b;
			++i.x;
		}
		++i.y;
	}
	free(temp_data);
}
