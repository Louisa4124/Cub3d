/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_switch_plan_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:05:03 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/03 22:00:21 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	switch_plan_inter_search(t_game *game, int data[4], int found)
{
	t_plan	*plan;
	int		wit;

	wit = 1;
	plan = game->plan[data[0]];
	while (data[1] >= 0 && data[1] <= data[2] && wit > 0 && data[3] != 0)
	{
		game->t = (plan[data[1]].a * game->u_rays.x + plan[data[1]].b \
				* game->u_rays.y + plan[data[1]].c * game->u_rays.z);
		if (game->t != 0)
			wit = intersect(game, &plan[data[1]], data[1], data[0], found);
		data[1] += data[3];
	}
	return (wit);
}

static void	switch_plan_get_data(t_game *game, int data[4], int axis)
{
if (axis == 0)
	{
		data[0] = axis;
		data[1] = game->pos.y;
		data[2] = game->map.y_size;
		data[3] =  math_sign_float(game->u_rays.y);	
	}
	else
	{
		data[0] = axis;
		data[1] = game->pos.x;
		data[2] = game->map.x_size;
		data[3] =  math_sign_float(game->u_rays.x);	
	}
}

int	switch_plan_algo(t_game *game)
{
	int	wit_y;
	int	wit_x;
	int	data[4];

	switch_plan_get_data(game, data, 0);
	wit_y = switch_plan_inter_search(game, data, 1);
	switch_plan_get_data(game, data, 1);
	wit_x = switch_plan_inter_search(game, data, wit_y);
	if (wit_y == 0 || wit_x == 0)
		return (get_color(game));
	else
		return (get_color_ceilling_floor(game));
}
