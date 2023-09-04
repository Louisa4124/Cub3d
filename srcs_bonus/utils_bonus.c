/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:57:21 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/04 14:47:32 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	rgb_to_hexa(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

float	math_vec_scalar_prod(t_vec3d u, t_vec3d v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

int	darken_color(int color, float d_ratio, float intensity)
{
	int	r;
	int	g;
	int	b;

	d_ratio = intensity / d_ratio ;
	if (d_ratio > 1)
		return (color);
	r = (((color >> 16) * d_ratio));
	g = (((color >> 8) & 255) * d_ratio);
	b = (color & 255) * d_ratio;
	return (r << 16 | g << 8 | b);
}

int	ft_randuint(int min, int max, int *n)
{
	unsigned int	c;
	int				fd;

	c = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (1);
	if (read(fd, &c, 1) == -1)
	{
		close (fd);
		return (-2);
	}
	close (fd);
	*n = c % (max + 1 - min) + min;
	return (0);
}

int	is_near(t_vec3d p1, t_vec3d p2, float e)
{
	t_vec3d	diff;

	diff = math_vec_op(p1, p2, '-');
	if (diff.x < -e || diff.x > e)
		return (0);
	if (diff.y < -e || diff.y > e)
		return (0);
	return (1);
}
