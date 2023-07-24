/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/07/24 22:04:24 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	ft_is_wall(t_display *data_th, int **layout, int u, int v)
{
	int	d;
	int	sumx;
	int	sumy;

	d = -data_th->plan[v][u].d;
	sumx = data_th->pos->x + data_th->tmp_point.x;
	sumy = data_th->pos->y + data_th->tmp_point.y;
	if ((data_th->close_t == 0 \
		|| data_th->t < data_th->close_t) && ((v == 0 \
		&& sumy < data_th->pos->y && d < data_th->map->y_size \
		&& (d - 1) >= 0 && layout[d - 1][sumx] == 1) \
		|| (v == 1 && sumx < data_th->pos->x && (d - 1) < data_th->map->x_size \
		&& (d - 1) >= 0 && layout[sumy][d - 1] == 1) \
		|| (v == 0 && sumy > data_th->pos->y && d < data_th->map->y_size \
		&& d >= 0 && layout[d][sumx] == 1) \
		|| (v == 1 && sumx > data_th->pos->x && d < data_th->map->x_size \
		&& d >= 0 && layout[sumy][d] == 1)))
		return (1);
	return (0);
}

int	intersect(t_display *data_th, t_plan *plan, int data[4], int wit)
{
	data_th->t = -(plan->a * data_th->pos->x + plan->b * \
		data_th->pos->y + plan->c * 0.5 + plan->d) / data_th->t;
	if (wit == 0 && data_th->t > data_th->close_t)
		return (-1);
	if (data_th->t <= 0)
		return (1);
	data_th->tmp_point.x = data_th->tmp_rays.x * data_th->t;
	data_th->tmp_point.y = data_th->tmp_rays.y * data_th->t;
	data_th->tmp_point.z = 0.5 + data_th->tmp_rays.z * data_th->t;
	if (data_th->tmp_point.z >= 1 || data_th->tmp_point.z <= 0 \
		|| (int)(data_th->pos->x + data_th->tmp_point.x) < 0 \
		|| (int)(data_th->pos->y + data_th->tmp_point.y) < 0 \
		|| (int)(data_th->pos->x + data_th->tmp_point.x) >= data_th->map->x_size \
		|| (int)(data_th->pos->y + data_th->tmp_point.y) >= data_th->map->y_size)
		return (-1);
	if (ft_is_wall(data_th, data_th->map->layout, data[1], data[0]))
	{
		data_th->close_t = data_th->t;
		data_th->tmp_plan.x = data[0];
		data_th->tmp_plan.y = data[1];
		data_th->tmp_plan.d = (int)-data_th->plan[data[0]][data[1]].d;
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
