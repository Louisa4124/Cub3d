/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/04 23:24:29 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3D_bonus.h"

static int	get_color_wall(t_tmp *data, int wall)
{
	int	x;
	int	y;

	if (wall % 2 == 1)
		x = (int)(((data->link->pos->y + data->point.y) - (int)(data->link-> \
			pos->y + data->point.y)) * data->link->texture->wall[wall].width);
	else
		x = (int)(((data->link->pos->x + data->point.x) - (int)(data->link-> \
			pos->x + data->point.x)) * data->link->texture->wall[wall].width);
	y = data->link->texture->wall[wall].height - (int)((data->point.z - \
		(int)(data->point.z)) * data->link->texture->wall[wall].height) - 1;
	return (*(unsigned int *)(data->link->texture->wall[wall].addr + y * \
		data->link->texture->wall[wall].ll + x * \
		(data->link->texture->wall[wall].bpp / 8)));
}

// Pour l’axe des x, les parties décimales à prendre sont celles de Ix et Iz.
// Pour l’axe des y, les parties décimales à prendre sont celles de Iy et Iz.

// int	get_color_ceilling_floor(t_tmp *data)
// {
// 	int	x;
// 	int	y;

// 	if (data->tmp_rays.z > 0)
// 		return (data->texture->ceiling);
// 	else
// 	{
// 		x = (int)(((data->pos->y + data->tmp_point.y) - (int)(data->pos->y + \
// 			data->tmp_point.y)) * data->texture->wall[2].width);
// 		y = data->texture->wall[2].height - (int)((data->tmp_point.z - \
// 			(int)(data->tmp_point.z)) * data->texture->wall[2].height) - 1;
// 		return (*(unsigned int *)(data->texture->wall[2].addr + y * data->texture->wall[2].ll + x * (data->texture->wall[2].bpp / 8)));
// 		//return (data->texture->floor);
// 	}
// }

int	get_color_ceilling_floor(t_tmp *data)
{
	if (data->rays.z > 0)
		return (data->link->texture->ceiling);
	else
		return (data->link->texture->floor);
}

int	get_color(t_tmp *data)
{
	data->point.x = data->rays.x * data->close_t;
	data->point.y = data->rays.y * data->close_t;
	data->point.z = 0.5 + data->rays.z * data->close_t;
	if (data->plan.x == 0 && (data->link->pos->y + data->point.y) < data-> \
		link->pos->y && (data->plan.d - 1) < data->link->map->y_size && \
		(data->plan.d - 1) >= 0 && data->link->map->layout[data->plan.d - 1] \
		[(int)(data->link->pos->x + data->point.x)] == 1)
		return (get_color_wall(data, 0));
	else if (data->plan.x == 1 && (data->link->pos->x + data->point.x) < \
		data->link->pos->x && (data->plan.d - 1) < data->link->map->x_size && \
		(data->plan.d - 1) >= 0 && data->link->map->layout[(int)(data->link-> \
		pos->y + data->point.y)][(int)(data->plan.d - 1)] == 1)
		return (get_color_wall(data, 1));
	else if (data->plan.x == 0 && (data->link->pos->y + data->point.y) > \
		data->link->pos->y && (data->plan.d) < data->link->map->y_size && \
		data->plan.d >= 0 && data->link->map->layout[(data->plan.d)][(int) \
		(data->link->pos->x + data->point.x)] == 1)
		return (get_color_wall(data, 2));
	else
		return (get_color_wall(data, 3));
}
