/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_switch_plan.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:05:03 by tlegrand          #+#    #+#             */
/*   Updated: 2023/06/30 15:43:14 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// plan = 0 -> y
// plan = 1 -> x
// i -> y         j -> x
static int	switch_plan_inter_search(t_game *game, int pos, int max, int id_plan, int found, int dir)
{
	int		wit;
	t_plan	*plan;

	wit = 1;
	plan = game->plan[id_plan];
	while (pos >= 0 && pos <= max && wit > 0 && dir != 0)
	{
		game->t = (plan[pos].a * game->u_rays.x + plan[pos].b \
				* game->u_rays.y + plan[pos].c * game->u_rays.z);
		if (game->t != 0)
			wit = intersect(game, &plan[pos], pos, id_plan, found);
		pos += dir;
	}
	return (wit);
}

int	switch_plan_algo(t_game *game)
{
	int	wit_y;
	int	wit_x;

	wit_y = switch_plan_inter_search(game, game->pos.y, game->map.y_size, 0, 1, math_sign_float(game->u_rays.y));
	wit_x = switch_plan_inter_search(game, game->pos.x, game->map.x_size, 1, wit_y, math_sign_float(game->u_rays.x));
	if (wit_y == 0 || wit_x == 0)
		return (get_color(game));
	else
		return (get_color_ceilling_floor(game));
}
