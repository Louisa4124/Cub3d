/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:39:15 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/20 17:01:27 by tlegrand         ###   ########.fr       */
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

unsigned int	*copy_img(unsigned int *image_data, int width, int height)
{
	unsigned int	*temp_data;

	temp_data = malloc(width * height * sizeof(unsigned int));
	if (!temp_data)
		return (NULL);
	ft_memcpy(temp_data, image_data, width * height * sizeof(unsigned int));
	return (temp_data);
}

			// if ((i.y + k.y) * width + (i.x + k.x) > width * height)
			// 	dprintf(2, "overflow \n");

int	ft_super_mod_cycle(int width, int height, t_vec2d i, t_vec2d k)
{
	return (0);
}

t_color	blur_image_avg(unsigned int *temp_data, t_vec2d i, int width, int height, int half_kernel)
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
			pixel = temp_data[((i.y + k.y) % height) * width + ((i.x + k.x) % width)];
			set_color(&c, (pixel >> 16) & 0xFF, (pixel >> 8) & 0xFF, pixel & 0xFF);
			add_color(&sum, c.r, c.g, c.b);
			++k.x;
		}
		++k.y;
	}
	return (sum);
}

void	blur_image(unsigned int *image_data, int width, int height)
{
	unsigned int	*temp_data;
	int				ker_size;
	int				half_ker;
	t_vec2d			i;
	t_color			sum;
	t_color			avg;

	temp_data = copy_img(image_data, width, height);
	if (temp_data == NULL)
		return ;
	ker_size = 25;
	half_ker = ker_size * 0.5;
	i.y = half_ker;
	while (i.y < height) 
	{
		i.x = half_ker;
		while (i.x < width) 
		{
			sum = blur_image_avg(temp_data, i, width, height, half_ker);
			set_color(&avg, sum.r / (ker_size * ker_size), sum.g / \
				(ker_size * ker_size), sum.b / (ker_size * ker_size));
			image_data[i.y * width + i.x] = (avg.r << 16) | (avg.g << 8) | avg.b;
			++i.x;
		}
		++i.y;
	}
	free(temp_data);
}
