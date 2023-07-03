/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:14:46 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/03 21:52:32 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	rgb_to_hexa(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static void	get_color_wall(t_game *game, int wall)
{
	int	x;
	int	y;

	if (wall % 2 == 1)
		x = (int)(((game->pos.y + game->point.y) - (int)(game->pos.y + \
			game->point.y)) * game->texture.wall[wall].width);
	else
		x = (int)(((game->pos.x + game->point.x) - (int)(game->pos.x + \
			game->point.x)) * game->texture.wall[wall].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - \
		(int)(game->point.z)) * game->texture.wall[wall].height) - 1;
	game->color = *(unsigned int *)(game->texture.wall[wall].addr + y * \
		game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8));
}

void	get_color_ceilling_floor(t_game *game)
{
	if (game->u_rays.z > 0)
		game->color = game->texture.ceiling;
	else
		game->color = game->texture.floor;
}

void	get_color(t_game *game)
{
	game->point.x = game->u_rays.x * game->close_t;
	game->point.y = game->u_rays.y * game->close_t;
	game->point.z = 0.5 + game->u_rays.z * game->close_t;
	if (game->u_plan.x == 0 && (game->pos.y + game->point.y) < game->pos.y \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.y_size \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 \
		&& game->map.layout[(int)(-game->plan[game->u_plan.x] \
		[game->u_plan.y].d - 1)][(int)(game->pos.x + game->point.x)] == 1)
		get_color_wall(game, 0);
	else if (game->u_plan.x == 1 && (game->pos.x + game->point.x) < game->pos.x \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.x_size \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 \
		&& game->map.layout[(int)(game->pos.y + game->point.y)][(int) \
		(-game->plan[game->u_plan.x][game->u_plan.y].d - 1)] == 1)
		get_color_wall(game, 1);
	else if (game->u_plan.x == 0 && (game->pos.y + game->point.y) > game->pos.y \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) < game->map.y_size \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) >= 0 \
		&& game->map.layout[(int)(-game->plan[game->u_plan.x][game->u_plan.y].d)] \
		[(int)(game->pos.x + game->point.x)] == 1)
		get_color_wall(game, 2);
	else
		get_color_wall(game, 3);
}
