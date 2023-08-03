/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:14:46 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/03 14:02:00 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	get_color_wall(t_tmp *data, int wall)
{
	int	x;
	int	y;

	if (wall % 2 == 1)
		x = (int)(((data->link->pos->y + data->tmp_point.y) - (int)(data->link->pos->y + \
			data->tmp_point.y)) * data->link->texture->wall[wall].width);
	else
		x = (int)(((data->link->pos->x + data->tmp_point.x) - (int)(data->link->pos->x + \
			data->tmp_point.x)) * data->link->texture->wall[wall].width);
	y = data->link->texture->wall[wall].height - (int)((data->tmp_point.z - \
		(int)(data->tmp_point.z)) * data->link->texture->wall[wall].height) - 1;
	return (*(unsigned int *)(data->link->texture->wall[wall].addr + y * \
		data->link->texture->wall[wall].ll + x * \
		(data->link->texture->wall[wall].bpp / 8)));
}

int	get_color_ceilling_floor(t_tmp *data)
{
	if (data->tmp_rays.z > 0)
		return (data->link->texture->ceiling);
	else
		return (data->link->texture->floor);
}

int	get_color(t_tmp *data)
{
	data->tmp_point.x = data->tmp_rays.x * data->close_t;
	data->tmp_point.y = data->tmp_rays.y * data->close_t;
	data->tmp_point.z = 0.5 + data->tmp_rays.z * data->close_t;
	if (data->tmp_plan.x == 0 && (data->link->pos->y + data->tmp_point.y) < data->link->pos->y \
		&& (data->tmp_plan.d - 1) < data->link->map->y_size && (data->tmp_plan.d - 1) \
		>= 0 && data->link->map->layout[data->tmp_plan.d - 1][(int)(data->link->pos->x + data->tmp_point.x)] == 1)
		return (get_color_wall(data, 0));
	else if (data->tmp_plan.x == 1 && (data->link->pos->x + data->tmp_point.x) < data->link->pos->x \
		&& (data->tmp_plan.d - 1) < data->link->map->x_size && (data->tmp_plan.d \
		- 1) >= 0 && data->link->map->layout[(int)(data->link->pos->y + data->tmp_point.y)][(int) \
		(data->tmp_plan.d - 1)] == 1)
		return (get_color_wall(data, 1));
	else if (data->tmp_plan.x == 0 && (data->link->pos->y + data->tmp_point.y) > data->link->pos->y \
		&& (data->tmp_plan.d) < data->link->map->y_size && \
		data->tmp_plan.d >= 0 \
		&& data->link->map->layout[(data->tmp_plan.d)][(int)(data->link->pos->x + \
		data->tmp_point.x)] == 1)
		return (get_color_wall(data, 2));
	else
		return (get_color_wall(data, 3));
}
