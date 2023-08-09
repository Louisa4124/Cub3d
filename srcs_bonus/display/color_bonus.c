/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:50:23 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/09 12:54:01 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	update_anim(t_igs *igs)
{
	if (igs->ms >= 0.02)
	{
		igs->ms -= 0.02;
		igs->sp->y += igs->sp->ry;
	}
	if (igs->sp->y >= igs->sp->ry * igs->sp->frame)
		igs->sp->y = 0;
}

int	get_color_sprite(t_igs *igs, t_vec3d point)
{
	t_vec3d	u;
	t_vec3d	w;
	float	n;
	float	r;

	u = (t_vec3d){point.x - igs->pos.x, point.y - igs->pos.y, 0};
	w = (t_vec3d){igs->plan.b, -igs->plan.a, 0};
	n = 1 / sqrt((w.x * w.x) + (w.y * w.y));
	r = 0.5 + (u.x * w.x * n + u.y * w.y * n);
	if (r < 0 || r >= 1)
		return (-1);
	update_anim(igs);
	return (extract_pixel(igs->sp->img, r * igs->sp->img.width, \
		(1 - point.z - (int) point.z) * igs->sp->ry + igs->sp->y));
}

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
		(data->link->texture->wall[wall].bpp >> 3)));
}

int	get_color_floor(t_tmp *data)
{
	int		x;
	int		y;
	float	res_x;
	float	res_y;
	float	t;

	data->close_t = -0.5 / (data->rays.z);
	t = -data->link->pos->z / data->rays.z;
	res_x = data->link->pos->x + (data->rays.x * t);
	res_y = data->link->pos->y + (data->rays.y * t);
	x = (int)(((res_x) - (int)(res_x)) * data->link->texture->w_floor.width);
	y = (int)(((res_y) - (int)(res_y)) * data->link->texture->w_floor.height);
	return (*(unsigned int *)(data->link->texture->w_floor.addr + y * \
		data->link->texture->w_floor.ll + \
		x * (data->link->texture->w_floor.bpp >> 3)));
}

int	get_color_ceiling(t_tmp *data)
{
	int		x;
	int		y;
	float	res_x;
	float	res_y;
	float	t;

	data->close_t = 0.5 / data->rays.z;
	t = (1 - data->link->pos->z) / data->rays.z;
	res_x = data->link->pos->x + (data->rays.x * t);
	res_y = data->link->pos->y + (data->rays.y * t);
	x = (int)(((res_x) - (int)(res_x)) * data->link->texture->w_ceiling.width);
	y = (int)(((res_y) - (int)(res_y)) * data->link->texture->w_ceiling.height);
	return (*(unsigned int *)(data->link->texture->w_ceiling.addr + y * \
		data->link->texture->w_ceiling.ll + \
		x * (data->link->texture->w_ceiling.bpp >> 3)));
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
