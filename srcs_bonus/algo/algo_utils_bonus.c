/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/08/03 22:39:41 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	ft_is_wall(t_tmp *data, int **layout, int u, int v)
{
	int	d;
	int	sumx;
	int	sumy;

	d = -data->link->plan[v][u].d;
	sumx = data->link->pos->x + data->point.x;
	sumy = data->link->pos->y + data->point.y;
	if ((data->close_t == 0 \
		|| data->t < data->close_t) && ((v == 0 \
		&& sumy < data->link->pos->y && d < data->link->map->y_size \
		&& (d - 1) >= 0 && layout[d - 1][sumx] == 1) \
		|| (v == 1 && sumx < data->link->pos->x && (d - 1) < data->link->map-> \
		x_size && (d - 1) >= 0 && layout[sumy][d - 1] == 1) \
		|| (v == 0 && sumy > data->link->pos->y && d < data->link->map->y_size \
		&& d >= 0 && layout[d][sumx] == 1) \
		|| (v == 1 && sumx > data->link->pos->x && d < data->link->map->x_size \
		&& d >= 0 && layout[sumy][d] == 1)))
		return (1);
	return (0);
}

int	intersect(t_tmp *data, t_plan *plan, int l_data[4], int wit)
{
	data->t = -(plan->a * data->link->pos->x + plan->b * \
		data->link->pos->y + plan->c * 0.5 + plan->d) / data->t;
	if (wit == 0 && data->t > data->close_t)
		return (-1);
	if (data->t <= 0)
		return (1);
	data->point.x = data->rays.x * data->t;
	data->point.y = data->rays.y * data->t;
	data->point.z = 0.5 + data->rays.z * data->t;
	if (data->point.z >= 1 || data->point.z <= 0 \
		|| (int)(data->link->pos->x + data->point.x) < 0 \
		|| (int)(data->link->pos->y + data->point.y) < 0 \
		|| (int)(data->link->pos->x + data->point.x) >= data->link->map->x_size \
		|| (int)(data->link->pos->y + data->point.y) >= data->link->map->y_size)
		return (-1);
	if (ft_is_wall(data, data->link->map->layout, l_data[1], l_data[0]))
	{
		data->close_t = data->t;
		data->plan.x = l_data[0];
		data->plan.y = l_data[1];
		data->plan.d = (int)-data->link->plan[l_data[0]][l_data[1]].d;
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
