/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:00 by lboudjem          #+#    #+#             */
/*   Updated: 2023/05/09 16:26:35 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_inter_plan_line(t_game *game, t_plan *plan, t_vec3d *inter, int x, int y)
{
	float	t;

	t = -(plan->a * game->camera.x + plan->b * game->camera.y + plan->c * \
		game->camera.z + plan->d);
	if (t == 0)
	{
		//pas un mur
		return (1);
	}
	if (t > 0)
	{
		inter->x = game->camera.x + (game->rays[x][y].x * t);
		inter->y = game->camera.y + (game->rays[x][y].y * t);
		inter->z = game->camera.z + (game->rays[x][y].z * t);
		if (inter->z >= 0 && inter->z < 1)
			return (0);
	}
	return (1);
}

// static int	in_map(t_map *map, int x, int y)
// {
// 	return (x >= 0 && x < map->x_size && y >= 0 && y < map->y_size 
// 			&& map->layout[y][x] == 1);
// }
