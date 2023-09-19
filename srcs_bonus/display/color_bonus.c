/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:50:23 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/19 18:47:16 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	get_color_wall(t_tmp *data, t_img wall, float pos, int n)
{
	int	x;
	int	y;

	if (n)
		x = (int)(((pos + data->point.y) \
			- (int)(pos + data->point.y)) * wall.width);
	else
		x = (int)(((pos + data->point.x) \
			- (int)(pos + data->point.x)) * wall.width);
	y = wall.height - (int)((data->point.z \
		- (int)(data->point.z)) * wall.height) - 1;
	return (extract_pixel(wall, x, y));
}

int	get_color_floor(t_tmp *data, t_img floor)
{
	float	res_x;
	float	res_y;
	float	t;
	int		offset;

	t = -data->link->pos->z / (data->rays.z);
	data->close_t = t;
	res_x = data->link->pos->x + (data->rays.x * t);
	res_y = data->link->pos->y + (data->rays.y * t);
	offset = ((int)(((res_y) - (int)(res_y)) * floor.height)) * floor.ll \
		+ ((int)(((res_x) - (int)(res_x)) * floor.width)) * (floor.bpp >> 3);
	if (offset < 0)
		offset = -offset;
	return (*(int *)(floor.addr + offset));
}

int	get_color_ceiling(t_tmp *data, t_img ceiling)
{
	int		x;
	int		y;
	float	res_x;
	float	res_y;
	float	t;

	data->close_t = data->link->pos->z / data->rays.z;
	t = (1 - data->link->pos->z) / data->rays.z;
	res_x = data->link->pos->x + (data->rays.x * t);
	res_y = data->link->pos->y + (data->rays.y * t);
	x = (int)(((res_x) - (int)(res_x)) * ceiling.width);
	y = (int)(((res_y) - (int)(res_y)) * ceiling.height);
	return (*(unsigned int *)(ceiling.addr + y * \
		ceiling.ll + \
		x * (ceiling.bpp >> 3)));
}

int	get_color(t_tmp *data, t_map *map, t_vec3d *pos)
{
	data->point.x = data->rays.x * data->close_t;
	data->point.y = data->rays.y * data->close_t;
	data->point.z = pos->z + data->rays.z * data->close_t;
	if (data->plan.x == 0 && (pos->y + data->point.y) < data-> \
		link->pos->y && (data->plan.d - 1) < map->y_size && \
		(data->plan.d - 1) >= 0 && map->layout[data->plan.d - 1] \
		[(int)(pos->x + data->point.x)] == 1)
		return (get_color_wall(data, data->link->texture->wall[0], pos->x, 0));
	else if (data->plan.x == 1 && (pos->x + data->point.x) < \
		pos->x && (data->plan.d - 1) < map->x_size && \
		(data->plan.d - 1) >= 0 && map->layout[(int)(data->link-> \
		pos->y + data->point.y)][(int)(data->plan.d - 1)] == 1)
		return (get_color_wall(data, data->link->texture->wall[2], pos->y, 1));
	else if (data->plan.x == 0 && (pos->y + data->point.y) > \
		pos->y && (data->plan.d) < map->y_size && \
		data->plan.d >= 0 && map->layout[(data->plan.d)][(int) \
		(pos->x + data->point.x)] == 1)
		return (get_color_wall(data, data->link->texture->wall[1], pos->x, 0));
	else
		return (get_color_wall(data, data->link->texture->wall[3], pos->y, 1));
}
