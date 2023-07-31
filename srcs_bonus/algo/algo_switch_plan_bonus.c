/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_switch_plan_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:05:03 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/24 22:11:05 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	switch_plan_inter_search(t_display *data_thread, int data[4], int found)
{
	t_plan	*plan;
	int		wit;

	if (data[3] == 0)
		return (1);
	wit = 1;
	plan = data_thread->plan[data[0]];
	while (data[1] >= 0 && data[1] <= data[2] && wit > 0)
	{
		data_thread->t = (plan[data[1]].a * data_thread->tmp_rays.x + \
			plan[data[1]].b * data_thread->tmp_rays.y + plan[data[1]].c * \
			data_thread->tmp_rays.z);
		if (data_thread->t != 0)
			wit = intersect(data_thread, &plan[data[1]], data, found);
		data[1] += data[3];
	}
	return (wit);
}

static void	switch_plan_get_data(t_display *data_thread, int data[4], int axis)
{
	if (axis == 0)
	{
		data[0] = axis;
		data[1] = data_thread->pos->y;
		data[2] = data_thread->map->y_size;
		data[3] = math_sign_float(data_thread->tmp_rays.y);
	}
	else
	{
		data[0] = axis;
		data[1] = data_thread->pos->x;
		data[2] = data_thread->map->x_size;
		data[3] = math_sign_float(data_thread->tmp_rays.x);
	}
}

int	switch_plan_algo(t_display *data_thread)
{
	int	wit_y;
	int	wit_x;
	int	data[4];

	switch_plan_get_data(data_thread, data, 0);
	wit_y = switch_plan_inter_search(data_thread, data, 1);
	switch_plan_get_data(data_thread, data, 1);
	wit_x = switch_plan_inter_search(data_thread, data, wit_y);
	if (wit_y == 0 || wit_x == 0)
		return (get_color(data_thread));
	else
		return (get_color_ceilling_floor(data_thread));
}
