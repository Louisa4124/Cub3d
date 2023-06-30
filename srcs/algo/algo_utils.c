/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/06/30 17:05:50 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_is_wall(t_game *game, int **layout, int u, int v)
{
	int	d;
	int	sumx;
	int	sumy;

	d = -game->plan[v][u].d;
	sumx = game->pos.x + game->point.x;
	sumy = game->pos.y + game->point.y;
	if ((game->close_t == 0 \
		|| game->t < game->close_t) && ((v == 0 \
		&& sumy < game->pos.y && d < game->map.y_size \
		&& (d - 1) >= 0 && layout[d - 1][sumx] == 1) \
		|| (v == 1 && sumx < game->pos.x && (d - 1) < game->map.x_size \
		&& (d - 1) >= 0 && layout[sumy][d - 1] == 1) \
		|| (v == 0 && sumy > game->pos.y && d < game->map.y_size \
		&& d >= 0 && layout[d][sumx] == 1) \
		|| (v == 1 && sumx > game->pos.x && d < game->map.x_size \
		&& d >= 0 && layout[sumy][d] == 1)))
		return (1);
	return (0);
}

int intersect(t_game *game, t_plan *plan, int u, int v, int wit)
{
	game->t = -(plan->a * game->pos.x + plan->b * \
		game->pos.y + plan->c * 0.5 + plan->d) / game->t;
	if (wit == 0 && game->t > game->close_t)
		return (-1);
	if (game->t > 0)
	{
		game->point.x = game->u_rays.x * game->t;
		game->point.y = game->u_rays.y * game->t;
		game->point.z = 0.5 + game->u_rays.z * game->t;
		if (game->point.z < 1 && game->point.z > 0
			&& (int)(game->pos.x + game->point.x) >= 0 \
			&& (int)(game->pos.y + game->point.y) >= 0 \
			&& (int)(game->pos.x + game->point.x) < game->map.x_size \
			&& (int)(game->pos.y + game->point.y) < game->map.y_size)
		{
			if (ft_is_wall(game, game->map.layout, u, v))
			{
				game->close_t = game->t;
				game->u_plan.x = v;
				game->u_plan.y = u;
				return (0);
			}
		}
		else
			return (-1);
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




// plan du sol : {0, 0, 1, 0}
// plan du plafond : {0, 0, 1, -1}
// rays entre -1.000 et 1.000
// NO -> 0
// SO -> 1
// WE -> 2
// EA -> 3