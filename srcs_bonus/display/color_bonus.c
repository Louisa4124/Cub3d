/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:14:46 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/24 22:09:02 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	get_color_wall(t_display *data, int wall)
{
	int	x;
	int	y;

	if (wall % 2 == 1)
		x = (int)(((data->pos->y + data->tmp_point.y) - (int)(data->pos->y + \
			data->tmp_point.y)) * data->texture->wall[wall].width);
	else
		x = (int)(((data->pos->x + data->tmp_point.x) - (int)(data->pos->x + \
			data->tmp_point.x)) * data->texture->wall[wall].width);
	y = data->texture->wall[wall].height - (int)((data->tmp_point.z - \
		(int)(data->tmp_point.z)) * data->texture->wall[wall].height) - 1;
	return (*(unsigned int *)(data->texture->wall[wall].addr + y * \
		data->texture->wall[wall].ll + x * \
		(data->texture->wall[wall].bpp / 8)));
}

int	get_color_ceilling_floor(t_display *data)
{
	if (data->tmp_rays.z > 0)
		return (data->texture->ceiling);
	else
		return (data->texture->floor);
}

int	get_color(t_display *data)
{
	data->tmp_point.x = data->tmp_rays.x * data->close_t;
	data->tmp_point.y = data->tmp_rays.y * data->close_t;
	data->tmp_point.z = 0.5 + data->tmp_rays.z * data->close_t;
	if (data->tmp_plan.x == 0 && (data->pos->y + data->tmp_point.y) < data->pos->y \
		&& (data->tmp_plan.d - 1) < data->map->y_size && (data->tmp_plan.d - 1) \
		>= 0 && data->map->layout[data->tmp_plan.d - 1][(int)(data->pos->x + data->tmp_point.x)] == 1)
		return (get_color_wall(data, 0));
	else if (data->tmp_plan.x == 1 && (data->pos->x + data->tmp_point.x) < data->pos->x \
		&& (data->tmp_plan.d - 1) < data->map->x_size && (data->tmp_plan.d \
		- 1) >= 0 && data->map->layout[(int)(data->pos->y + data->tmp_point.y)][(int) \
		(data->tmp_plan.d - 1)] == 1)
		return (get_color_wall(data, 1));
	else if (data->tmp_plan.x == 0 && (data->pos->y + data->tmp_point.y) > data->pos->y \
		&& (data->tmp_plan.d) < data->map->y_size && \
		data->tmp_plan.d >= 0 \
		&& data->map->layout[(data->tmp_plan.d)][(int)(data->pos->x + \
		data->tmp_point.x)] == 1)
		return (get_color_wall(data, 2));
	else
		return (get_color_wall(data, 3));
}
