/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_switch_plan_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:05:03 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/09 14:02:57 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	search_sprite(t_tmp *data, int *color)
{
	t_igs	*igs;
	int		s;
	int		i;

	i = 0;
	s = 1;
	igs = data->link->igs;
	while (i < N_IGS && s)
	{
		if (igs[i].sp)
			s = intersprite(data, &igs[i], *data->link->pos, color);
		++i;
	}
	return (s);
}

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
		data->t = (plan[l_data[1]].a * data->rays.x + \
			plan[l_data[1]].b * data->rays.y + plan[l_data[1]].c * \
			data->rays.z);
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
		l_data[3] = math_sign_float(data->rays.y);
	}
	else
	{
		l_data[0] = axis;
		l_data[1] = data->link->pos->x;
		l_data[2] = data->link->map->x_size;
		l_data[3] = math_sign_float(data->rays.x);
	}
}

int	switch_plan_algo(t_tmp *data)
{
	int	l_data[4];
	int	wit_y;
	int	wit_x;
	int	s;
	int	color;

	s = 1;
	s = search_sprite(data, &color);
	switch_plan_get_data(data, l_data, 0);
	wit_y = switch_plan_inter_search(data, l_data, s);
	switch_plan_get_data(data, l_data, 1);
	wit_x = switch_plan_inter_search(data, l_data, wit_y);
	if (wit_y == 0 || wit_x == 0)
		color = get_color(data);
	else if (s != 0 && data->rays.z > 0)
		color = data->link->texture->ceiling;
	else if (s != 0)
		color = get_color_floor(data, data->link->texture->t_floor);
	return (color);
}
