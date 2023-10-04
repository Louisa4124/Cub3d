/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_doors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:54:51 by tlegrand          #+#    #+#             */
/*   Updated: 2023/10/04 13:32:38 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static	int	is_door_x(t_map *map, int y, int x)
{
	if (x < 1 || x >= map->x_size)
		return (0);
	if (map->layout[y][x - 1] != 1 || map->layout[y][x + 1] != 1)
		return (0);
	return (1);
}

static	int	get_n_doors(t_map *map)
{
	int	n;
	int	i;
	int	j;

	n = 0;
	i = 0;
	while (i < map->y_size)
	{
		j = 0;
		while (j < map->x_size)
		{
			if (map->layout[i][j] == 2)
			{
				if (is_door_x(map, i, j))
					++n;
				else
					map->layout[i][j] = 0;
			}
			++j;
		}
		++i;
	}
	return (n);
}

static int	get_door(t_door *door, int y, int x, t_game *game)
{
	door->plan = (t_plan)(t_plan){0, 1, 0, -1.5};
	door->plan.d -= y;
	door->pos = (t_vec3d){x, y, 0};
	door->pos.x += 0.5;
	door->pos.y += 0.5;
	door->status = 0;
	door->count = 40;
	door->offset = 0.01;
	door->t = 0;
	door->img = &game->sprite[17].img;
	return (0);
}

int	parser_doors(t_game *game)
{
	int	i;
	int	j;
	int	n;

	game->n_doors = get_n_doors(&game->map);
	if (game->n_doors == 0)
		return (0);
	game->doors = ft_calloc(game->n_doors, sizeof(t_door));
	if (game->doors == NULL)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 1);
	n = 0;
	i = -1;
	while (++i < game->map.y_size)
	{
		j = -1;
		while (++j < game->map.x_size)
		{
			if (game->map.layout[i][j] == 2)
			{
				get_door(&game->doors[n], i, j, game);
				++n;
			}
		}
	}
	return (0);
}
