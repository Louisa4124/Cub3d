/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/08/16 14:37:24 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	intersprite(t_tmp *data, t_igs *igs, t_vec3d pos, int *color)
{
	t_vec3d	point;
	t_vec3d	dif;
	float	t;
	float	d;

	t = igs->plan.a * data->rays.x + igs->plan.b * data->rays.y;
	if (t == 0)
		return (1);
	t = -(igs->plan.a * pos.x + igs->plan.b * pos.y + igs->plan.d) / t;
	if (t <= 0)
		return (1);
	point.x = pos.x + data->rays.x * t;
	point.y = pos.y + data->rays.y * t;
	point.z = 0.5 + data->rays.z * t;
	if (point.z >= 1 || point.z < 0)
		return (1);
// // bloquer ici tout les intersection trop eloigne du centre du sprite
	// dif = math_vec_op(point, igs->pos, '-');
	// d = sqrt(dif.x * dif.x + dif.y * dif.y + dif.z * dif.z);
	// if (d > igs->sp->img.width)
	// {
	// 	dprintf(2, "out by x\n");
	// 	return (1);
	// }
	*color = get_color_sprite(igs, point);
	if ((*color >> 24))
		return (1);
	data->close_t = t;
	return (0);
}

// here jsut in case
static int	ft_is_wall2(t_tmp *data, int **layout, int v, int d)
{
	int	sumx;
	int	sumy;

	sumx = data->link->pos->x + data->point.x;
	sumy = data->link->pos->y + data->point.y;
	if (data->close_t == 0 || data->t < data->close_t) 
	{
		if (v == 0)
		{
			if (sumy < data->link->pos->y && (d - 1) < data->link->map->y_size && (d - 1) >= 0 && layout[d - 1][sumx] == 1)
				return (1);
			if (sumy > data->link->pos->y && d < data->link->map->y_size && d >= 0 && layout[d][sumx] == 1)
				return (1);
		}
		if (v == 1)
		{
			if (sumx < data->link->pos->x && (d - 1) < data->link->map->x_size && (d - 1) >= 0 && layout[sumy][d - 1] == 1)
				return (1);
			if (sumx > data->link->pos->x && d < data->link->map->x_size && d >= 0 && layout[sumy][d] == 1)
				return (1);
		}
	}
	return (0);
}

static int	ft_is_wall(t_tmp *data, int **layout, int v, int d)
{
	int	sumx;
	int	sumy;

	sumx = data->link->pos->x + data->point.x;
	sumy = data->link->pos->y + data->point.y;
	if (data->close_t == 0 || data->t < data->close_t) 
	{
		if (v == 0 && d < data->link->map->y_size)
		{
			if ((sumy < data->link->pos->y && (d - 1) >= 0 \
				&& layout[d - 1][sumx] == 1)
				|| (sumy > data->link->pos->y && d >= 0 
				&& layout[d][sumx] == 1))
				return (1);
		}
		else
		{
			if ((sumx < data->link->pos->x && (d - 1) >= 0 \
				&& layout[sumy][d - 1] == 1)
				|| (sumx > data->link->pos->x 
				&& d >= 0 && layout[sumy][d] == 1))
				return (1);
		}
	}
	return (0);
}

int	intersect(t_tmp *data, t_plan plan, t_vec3d pos, int coord[2])
{
	t_map	*map;

	map = data->link->map;
	data->point.x = data->rays.x * data->t;
	data->point.y = data->rays.y * data->t;
	data->point.z = 0.5 + data->rays.z * data->t;
	if (data->point.z >= 1 || data->point.z <= 0 \
		|| (int)(pos.x + data->point.x) < 0 \
		|| (int)(pos.y + data->point.y) < 0 \
		|| (int)(pos.x + data->point.x) >= map->x_size \
		|| (int)(pos.y + data->point.y) >= map->y_size)
		return (-1);
	if (ft_is_wall(data, map->layout, coord[0], -plan.d))
	{
		data->close_t = data->t;
		data->plan.x = coord[0];
		data->plan.y = coord[1];
		data->plan.d = (int)-plan.d;
		return (0);
	}
	return (1);
}

int	math_sign_float(float f)
{
	if (f < 0)
		return (-1);
	else if (f > 0)
		return (1);
	return (0);
}
