/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_switch_plan_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:05:03 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/04 14:51:36 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	search_sprite(t_tmp *data)
{
	t_igs	*igs;
	int		wit_s;
	int		wit_d;
	int		i;

	wit_d = 1;
	i = 0;
	while (wit_d && i < *data->link->n_doors)
	{
		wit_d = interdoor(data, &data->link->door[i], *data->link->pos, wit_d);
		++i;
	}
	igs = data->link->igs;
	wit_s = 1;
	i = 0;
	while (i < N_IGS && wit_s)
	{
		if (igs[i].sp)
			wit_s = intersprite(data, &igs[i], *data->link->pos, wit_d);
		++i;
	}
	if (wit_d == 0 || wit_s == 0)
		return (0);
	return (1);
}

static int	switch_plan_inter_search_y(t_tmp *data, int idx[2], \
	int dir, int found)
{
	t_plan	*plan;
	int		wit;

	if (dir == 0)
		return (1);
	wit = 1;
	plan = data->link->plan[0];
	while (idx[0] >= 0 && idx[0] <= idx[1] && wit > 0)
	{
		data->t = (plan[idx[0]].b * data->rays.y \
			+ plan[idx[0]].c * data->rays.z);
		if (data->t != 0)
		{
			data->t = -(plan[idx[0]].b * data->link->pos->y + \
				plan[idx[0]].c * data->link->pos->z + plan[idx[0]].d) / data->t;
			if (found == 0 && data->t > data->close_t)
				return (-1);
			if (data->t > 0)
				wit = intersect(data, plan[idx[0]], *data->link->pos, \
					(int [2]){0, idx[0]});
		}
		idx[0] += dir;
	}
	return (wit);
}

static int	switch_plan_inter_search_x(t_tmp *data, int idx[2], \
	int dir, int found)
{
	t_plan	*plan;
	int		wit;

	if (dir == 0)
		return (1);
	wit = 1;
	plan = data->link->plan[1];
	while (idx[0] >= 0 && idx[0] <= idx[1] && wit > 0)
	{
		data->t = (plan[idx[0]].a * data->rays.x \
			+ plan[idx[0]].c * data->rays.z);
		if (data->t != 0)
		{
			data->t = -(plan[idx[0]].a * data->link->pos->x + \
				plan[idx[0]].c * data->link->pos->z + plan[idx[0]].d) / data->t;
			if (found == 0 && data->t > data->close_t)
				return (-1);
			if (data->t > 0)
				wit = intersect(data, plan[idx[0]], *data->link->pos, \
					(int [2]){1, idx[0]});
		}
		idx[0] += dir;
	}
	return (wit);
}

int	switch_plan_algo(t_tmp *data)
{
	int	idx[2];
	int	wit_y;
	int	wit_x;
	int	s;

	s = 1;
	s = search_sprite(data);
	idx[0] = data->link->pos->y;
	idx[1] = data->link->map->y_size;
	wit_y = switch_plan_inter_search_y(data, idx, \
		math_sign_float(data->rays.y), s);
	idx[0] = data->link->pos->x;
	idx[1] = data->link->map->x_size;
	wit_x = switch_plan_inter_search_x(data, idx, \
		math_sign_float(data->rays.x), wit_y);
	if (wit_y == 0 || wit_x == 0)
		data->color = get_color(data, data->link->map, data->link->pos);
	else if (s != 0 && data->rays.z > 0)
		data->color = data->link->texture->ceiling;
	else if (s != 0)
		data->color = get_color_floor(data, data->link->texture->t_floor);
	return (data->color);
}
