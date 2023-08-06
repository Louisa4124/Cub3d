/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:57:21 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/06 17:12:28 by tlegrand         ###   ########.fr       */
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

/**
 * @brief darken based on distance with intersectio point
 * 
 * @param d_ratio distance (close_t)
 * @param intensity 
 * @return int 
 */
int	darken_color(int color, float d_ratio, float intensity)
{
	t_color	ret;

	d_ratio = intensity / d_ratio ;
	if (d_ratio > 1)
		return (color);
	ret.r = (int)(((color >> 16) * d_ratio)) << 16;
	ret.g = (int)(((color >> 8) & 255) * d_ratio) << 8;
	ret.b = (int)(color & 255) *d_ratio;
	return (ret.r | ret.g | ret.b);
}
