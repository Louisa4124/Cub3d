/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:14:59 by louisa            #+#    #+#             */
/*   Updated: 2023/05/07 22:15:21 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

inline t_vec	vec_rot_x(t_vec v, float rad)
{
	t_vec	new;

	new.x = v.x;
	new.y = v.y * cos(rad) + v.z * -sin(rad);
	new.z = v.y * sin(rad) + v.z * cos(rad);
	return (new);
}

inline t_vec	vec_rot_y(t_vec v, float rad)
{
	t_vec	new;

	new.x = v.x * cos(rad) + v.z * sin(rad);
	new.y = v.y;
	new.z = v.x * -sin(rad) + v.z * cos(rad);
	return (new);
}

inline t_vec	vec_rot_z(t_vec v, float rad)
{
	t_vec	new;

	new.x = v.x * cos(rad) + v.y * -sin(rad);
	new.y = v.x * sin(rad) + v.y * cos(rad);
	new.z = v.z;
	return (new);
}