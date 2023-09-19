/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:14:46 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/19 21:05:51 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	rgb_to_hexa(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static int	get_color_wall(t_game *game, int wall)
{
	int	x;
	int	y;

	if (wall == 0)
		x = (int)(((game->pos.x + game->point.x) - (int)(game->pos.x + \
			game->point.x)) * game->texture.wall[wall].width);
	else if (wall == 1)
		x = game->texture.wall[wall].width - 1 - (int)(((game->pos.x + game->point.x) \
			- (int)(game->pos.x + game->point.x)) * game->texture.wall[wall].width);
	else if (wall == 2)
		x = game->texture.wall[wall].width - 1 - (int)(((game->pos.y + game->point.y) \
		- (int)(game->pos.y + game->point.y)) * game->texture.wall[wall].width);
	else if (wall == 3)
		x = (int)(((game->pos.y + game->point.y) - (int)(game->pos.y + \
			game->point.y)) * game->texture.wall[wall].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - \
		(int)(game->point.z)) * game->texture.wall[wall].height) - 1;
	return (*(unsigned int *)(game->texture.wall[wall].addr + y * \
		game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp >> 3)));
}

int	get_color(t_game *game)
{
	game->point.x = game->u_rays.x * game->close_t;
	game->point.y = game->u_rays.y * game->close_t;
	game->point.z = 0.5 + game->u_rays.z * game->close_t;
	if (game->u_plan.x == 0 && (game->pos.y + game->point.y) < game->pos.y \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < \
		game->map.y_size && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d \
		- 1) >= 0 && game->map.layout[(int)(-game->plan[game->u_plan.x] \
		[game->u_plan.y].d - 1)][(int)(game->pos.x + game->point.x)] == 1)
		return (get_color_wall(game, 0));
	else if (game->u_plan.x == 1 && (game->pos.x + game->point.x) < game->pos.x \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < \
		game->map.x_size && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d \
		- 1) >= 0 && game->map.layout[(int)(game->pos.y + game->point.y)][(int) \
		(-game->plan[game->u_plan.x][game->u_plan.y].d - 1)] == 1)
		return (get_color_wall(game, 2));
	else if (game->u_plan.x == 0 && (game->pos.y + game->point.y) > game->pos.y \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) < \
		game->map.y_size && (int)(-game->plan[game->u_plan.x] \
		[game->u_plan.y].d) >= 0 && game->map.layout[(int)(-game->plan \
		[game->u_plan.x][game->u_plan.y].d)] \
		[(int)(game->pos.x + game->point.x)] == 1)
		return (get_color_wall(game, 1));
	else
		return (get_color_wall(game, 3));
}
