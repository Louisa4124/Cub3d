/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:14:59 by louisa            #+#    #+#             */
/*   Updated: 2023/05/08 13:02:00 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_vec3d	ft_rotate_vec_x(t_vec3d v, float rad)
{
	t_vec3d	cpy;

	cpy.x = v.x;
	cpy.y = v.y * cos(rad) + v.z * -sin(rad);
	cpy.z = v.y * sin(rad) + v.z * cos(rad);
	return (cpy);
}

t_vec3d	ft_rotate_vec_y(t_vec3d v, float rad)
{
	t_vec3d	cpy;

	cpy.x = v.x * cos(rad) + v.z * sin(rad);
	cpy.y = v.y;
	cpy.z = v.x * -sin(rad) + v.z * cos(rad);
	return (cpy);
}

t_vec3d	ft_rotate_vec_z(t_vec3d v, float rad)
{
	t_vec3d	cpy;

	cpy.x = v.x * cos(rad) + v.y * -sin(rad);
	cpy.y = v.x * sin(rad) + v.y * cos(rad);
	cpy.z = v.z;
	return (cpy);
}