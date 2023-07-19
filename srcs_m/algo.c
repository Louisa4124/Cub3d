/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/07/19 11:37:18 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	ft_is_wall(t_game *game, int **layout, int u, int v)
{
	int	d;
	int	sumx;
	int	sumy;

	d = -game->plan[v][u].d;
	sumx = game->pos.x + game->point.x;
	sumy = game->pos.y + game->point.y;
	if ((game->close_t == 0 
		|| game->t < game->close_t) && ((v == 0 
		&& sumy < game->pos.y && d < game->map.y_size 
		&& (d - 1) >= 0 && layout[d - 1][sumx] == 1) 
		|| (v == 1 && sumx < game->pos.x && (d - 1) < game->map.x_size 
		&& (d - 1) >= 0 && layout[sumy][d - 1] == 1)
		|| (v == 0 && sumy > game->pos.y && d < game->map.y_size 
		&& d >= 0 && layout[d][sumx] == 1)
		|| (v == 1 && sumx > game->pos.x&& d < game->map.x_size 
		&& d >= 0 && layout[sumy][d] == 1)))
		return (1);
	return (0);
}

static void	intersect(t_game *game, int u, int v)
{
	game->t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * \
		game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / game->t;
	if (game->t > 0)
	{
		game->point.x = game->u_rays.x * game->t;
		game->point.y = game->u_rays.y * game->t;
		game->point.z = 0.5 + game->u_rays.z * game->t;
		if (game->point.z < 1 && game->point.z > 0
			&& (int)(game->pos.x + game->point.x) >= 0 
			&& (int)(game->pos.y + game->point.y) >= 0 
			&& (int)(game->pos.x + game->point.x) < game->map.x_size 
			&& (int)(game->pos.y + game->point.y) < game->map.y_size)
		{
			if (ft_is_wall(game, game->map.layout, u, v))
			{
				game->close_t = game->t;
				game->u_plan.x = v;
				game->u_plan.y = u;
			}
		}
	}
}

void	ft_switch_plan(t_game *game)
{
	int v;
	int	u;
	int	switch_p;
	
	v = 0;
	while (v < 2)
	{
		if (v == 0)
			switch_p = game->map.y_size;
		else
			switch_p = game->map.x_size;
		u = -1;
		while (++u <= switch_p)
		{
			game->t = (game->plan[v][u].a * game->u_rays.x + game->plan[v][u].b \
				 * game->u_rays.y + game->plan[v][u].c * game->u_rays.z);
			if (game->t != 0)
				intersect(game, u, v);
			else
				get_color_ceilling_floor(game);
		}
		++v;
	}
	if (game->close_t != 0 && game->u_plan.x != 3 && game->u_plan.y != -7)
		get_color(game);
}
