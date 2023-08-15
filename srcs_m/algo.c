/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/08/15 10:51:52 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	ft_is_wall(t_game *data, int **layout, int u, int v)
{
	int	d;
	int	sumx;
	int	sumy;

	d = -data->plan[v][u].d;
	sumx = data->pos.x + data->point.x;
	sumy = data->pos.y + data->point.y;
	if ((data->close_t == 0 \
		|| data->t < data->close_t) && ((v == 0 \
		&& sumy < data->pos.y && d < data->map.y_size \
		&& (d - 1) >= 0 && layout[d - 1][sumx] == 1) \
		|| (v == 1 && sumx < data->pos.x && (d - 1) < data->map. \
		x_size && (d - 1) >= 0 && layout[sumy][d - 1] == 1) \
		|| (v == 0 && sumy > data->pos.y && d < data->map.y_size \
		&& d >= 0 && layout[d][sumx] == 1) \
		|| (v == 1 && sumx > data->pos.x && d < data->map.x_size \
		&& d >= 0 && layout[sumy][d] == 1)))
		return (1);
	return (0);
}

int	intersect(t_game *data, t_plan *plan, int l_data[4], int wit)
{
	data->t = -(plan->a * data->pos.x + plan->b * \
		data->pos.y + plan->c * 0.5 + plan->d) / data->t;
	if (wit == 0 && data->t > data->close_t)
		return (-1);
	if (data->t <= 0)
		return (1);
	data->point.x = data->u_rays.x * data->t;
	data->point.y = data->u_rays.y * data->t;
	data->point.z = 0.5 + data->u_rays.z * data->t;
	if (data->point.z >= 1 || data->point.z <= 0 \
		|| (int)(data->pos.x + data->point.x) < 0 \
		|| (int)(data->pos.y + data->point.y) < 0 \
		|| (int)(data->pos.x + data->point.x) >= data->map.x_size \
		|| (int)(data->pos.y + data->point.y) >= data->map.y_size)
		return (-1);
	if (ft_is_wall(data, data->map.layout, l_data[1], l_data[0]))
	{
		data->close_t = data->t;
		data->u_plan.x = l_data[0];
		data->u_plan.y = l_data[1];
		data->u_plan.d = (int)-data->plan[l_data[0]][l_data[1]].d;
		return (0);
	}
	return (1);
}

static int	switch_plan_inter_search(t_game *data, int l_data[4], int found)
{
	t_plan	*plan;
	int		wit;

	if (l_data[3] == 0)
		return (1);
	wit = 1;
	plan = data->plan[l_data[0]];
	while (l_data[1] >= 0 && l_data[1] <= l_data[2] && wit > 0)
	{
		data->t = (plan[l_data[1]].a * data->u_rays.x + \
			plan[l_data[1]].b * data->u_rays.y + plan[l_data[1]].c * \
			data->u_rays.z);
		if (data->t != 0)
			wit = intersect(data, &plan[l_data[1]], l_data, found);
		l_data[1] += l_data[3];
	}
	return (wit);
}

static void	switch_plan_get_data(t_game *data, int l_data[4], int axis)
{
	if (axis == 0)
	{
		l_data[0] = axis;
		l_data[1] = data->pos.y;
		l_data[2] = data->map.y_size;
		l_data[3] = math_sign_float(data->u_rays.y);
	}
	else
	{
		l_data[0] = axis;
		l_data[1] = data->pos.x;
		l_data[2] = data->map.x_size;
		l_data[3] = math_sign_float(data->u_rays.x);
	}
}

int	switch_plan_algo(t_game *data)
{
	int	wit_y;
	int	wit_x;
	int	l_data[4];

	switch_plan_get_data(data, l_data, 0);
	wit_y = switch_plan_inter_search(data, l_data, 1);
	switch_plan_get_data(data, l_data, 1);
	wit_x = switch_plan_inter_search(data, l_data, wit_y);
	if (wit_y == 0 || wit_x == 0)
		return (get_color(data));
	else if (data->u_rays.z > 0)
		return (data->texture.ceiling);
	else
		return (data->texture.floor);
}
