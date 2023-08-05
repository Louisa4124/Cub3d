/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/05 13:33:40 by lboudjem         ###   ########.fr       */
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

int	get_color_floor(t_tmp *data)
{
	int	x;
	int	y;
	float result_x;
	float result_y;
	float	t;

	t = -data->link->pos->z / data->rays.z;
	result_x = data->link->pos->x + (data->rays.x * t);
	result_y = data->link->pos->y + (data->rays.y * t);
	x = (int)(((result_x) - (int)(result_x)) * data->link->texture->wall[2].width);
	y = (int)(((result_y) - (int)(result_y)) * data->link->texture->wall[2].height);
	return (*(unsigned int *)(data->link->texture->wall[2].addr + y * \
		data->link->texture->wall[2].ll + x * (data->link->texture->wall[2].bpp / 8)));
}

int	get_color_ceiling(t_tmp *data)
{
	int	x;
	int	y;
	float result_x;
	float result_y;
	float	t;

	t = (1 - data->link->pos->z) / data->rays.z;
	result_x = data->link->pos->x + (data->rays.x * t);
	result_y = data->link->pos->y + (data->rays.y * t);
	x = (int)(((result_x) - (int)(result_x)) * data->link->texture->wall[2].width);
	y = (int)(((result_y) - (int)(result_y)) * data->link->texture->wall[2].height);
	return (*(unsigned int *)(data->link->texture->wall[2].addr + y * \
		data->link->texture->wall[2].ll + x * (data->link->texture->wall[2].bpp / 8)));
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
