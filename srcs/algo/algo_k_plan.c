/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_k_plan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:02:40 by tlegrand          #+#    #+#             */
/*   Updated: 2023/06/30 16:08:32 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	k_plan_inter_search(t_game *game, int *pos, int max, int plan, int *found, int dir, int limit)
{
	int	wit;
	int	i;

	wit = 1;
	i = 0;
	if (dir == 0)
		return (-1);
	while (wit > 0 && *pos >= 0 && *pos <= limit && i < max)
	{
		game->t = (game->plan[plan][*pos].a * game->u_rays.x + game->plan[plan][*pos].b \
				* game->u_rays.y + game->plan[plan][*pos].c * game->u_rays.z);
		if (game->t != 0)
			wit = intersect(game, &game->plan[plan][*pos], *pos, plan, *found);
		*pos += dir;
		++i;
	}
	if (*pos < 0 || *pos > limit)
		return (-1);
	if (wit == 0)
		*found = 0;
	return (wit);
}

// rx ratio de x pour 1y
// ry ratio de y pour 1x  
// return k > 0 for rx 
// return k < 0 for ry
static int	ft_give_me_ratio(float x, float y)
{
	float	r_x;
	float	r_y;
	int		kx;
	int		ky;

	r_x = x / y;
	r_y = y / x;
	kx = r_x;
	ky = r_y;
	if (kx)
		return (ft_abs(kx));
	else if (ky)
		return (-ft_abs(ky));
	return (0);
}

int	k_plan_algo(t_game *game)
{
	int		k;
	int		pos_x;
	int		pos_y;
	int		wit_y;
	int		wit_x;
	int		dir_x;
	int		dir_y;
	int		found;

	k = ft_give_me_ratio(game->u_rays.x, game->u_rays.y);
	pos_x = game->pos.x;
	pos_y = game->pos.y;
	dir_x = math_sign_float(game->u_rays.x);
	dir_y = math_sign_float(game->u_rays.y);
	wit_x = 1;
	wit_y = 1;
	found = 1;
	while (wit_x > 0 || wit_y > 0)
	{
		if (k > 0)
		{
			if (wit_x > 0)
				wit_x = k_plan_inter_search(game, &pos_x, 1, 1, &found, dir_x, game->map.x_size);
			if (wit_y > 0)
				wit_y = k_plan_inter_search(game, &pos_y, k, 0, &found, dir_y, game->map.y_size);
		}
		else if (k < 0)
		{
			if (wit_y > 0)
				wit_y = k_plan_inter_search(game, &pos_y, 1, 0, &found, dir_y, game->map.y_size);
			if (wit_x > 0)
				wit_x = k_plan_inter_search(game, &pos_x, -k, 1, &found, dir_x, game->map.x_size);
		}
		else
		{
			if (wit_x > 0)
				wit_x = k_plan_inter_search(game, &pos_x, 1, 1, &found, dir_x, game->map.x_size);
			if (wit_y > 0)
				wit_y = k_plan_inter_search(game, &pos_y, 1, 0, &found, dir_y, game->map.y_size);
		}
	}
	if (found == 0)
		return (get_color(game));
	else
		return (get_color_ceilling_floor(game));
}
