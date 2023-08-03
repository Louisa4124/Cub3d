/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_switch_plan_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:05:03 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/03 13:57:45 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	switch_plan_inter_search(t_tmp *data, int l_data[4], int found)
{
	t_plan	*plan;
	int		wit;

	if (l_data[3] == 0)
		return (1);
	wit = 1;
	plan = data->link->plan[l_data[0]];
	while (l_data[1] >= 0 && l_data[1] <= l_data[2] && wit > 0)
	{
		data->t = (plan[l_data[1]].a * data->tmp_rays.x + \
			plan[l_data[1]].b * data->tmp_rays.y + plan[l_data[1]].c * \
			data->tmp_rays.z);
		if (data->t != 0)
			wit = intersect(data, &plan[l_data[1]], l_data, found);
		l_data[1] += l_data[3];
	}
	return (wit);
}

static void	switch_plan_get_data(t_tmp *data, int l_data[4], int axis)
{
	if (axis == 0)
	{
		l_data[0] = axis;
		l_data[1] = data->link->pos->y;
		l_data[2] = data->link->map->y_size;
		l_data[3] = math_sign_float(data->tmp_rays.y);
	}
	else
	{
		l_data[0] = axis;
		l_data[1] = data->link->pos->x;
		l_data[2] = data->link->map->x_size;
		l_data[3] = math_sign_float(data->tmp_rays.x);
	}
}

int	switch_plan_algo(t_tmp *data)
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
	else
		return (get_color_ceilling_floor(data));
}
