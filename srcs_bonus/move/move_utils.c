/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:56:23 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/05 12:25:15 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_jump(t_game *game)
{
	if (game->jump == 1)
	{
		if (game->pos.z < 0.8)
			game->pos.z += (sqrt(2 * G * 0.2)) / 80 ;
		else
			game->jump = 2;
	}
	if (game->jump == 2)
	{
		if (game->pos.z > 0.5)
			game->pos.z -= (sqrt(2 * G * 0.2)) / 70;
		else
			game->jump = 0;
	}
}

int	ft_in_wall(t_map *map, int x, int y)
{
	if (x > map->x_size || y > map->y_size)
		return (0);
	if (x < 0 || y < 0)
		return (0);
	if (map->layout[y][x] == 1 || map->layout[y][x] == 2)
		return (1);
	return (0);
}
