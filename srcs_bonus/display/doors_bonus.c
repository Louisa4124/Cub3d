/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:46:45 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/04 18:22:01 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	sort_doors(t_door *doors, int n_doors)
{
	t_door	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < n_doors)
	{
		j = i;
		while (j < n_doors)
		{
			if (doors[i].t > doors[j].t)
			{
				tmp = doors[i];
				doors[i] = doors[j];
				doors[j] = tmp;
			}
			++j;
		}
		++i;
	}
}

void	update_doors_dist(t_door *doors, t_vec3d *pos, int n_doors)
{
	t_vec3d	diff;
	int		i;

	i = 0;
	while (i < n_doors)
	{
		diff = (t_vec3d){doors[i].pos.x - pos->x, doors[i].pos.y - pos->y, \
			doors[i].pos.z - pos->z};
		doors[i].t = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
		++i;
	}
	sort_doors(doors, n_doors);
}

int	is_near_door(t_game *game, t_door *doors, t_vec3d *pos)
{
	int	i;

	i = 0;
	while (i < game->n_doors)
	{
		if (doors[i].status != 0)
		{
			++i;
			continue ;
		}
		if (is_near(doors[i].pos, *pos, 2.0))
			return (i);
		++i;
	}
	return (-1);
}

void	update_door(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->n_doors)
	{
		if (game->doors[i].status == 0)
		{
			++i;
			continue ;
		}
		if (game->doors[i].count == 45 && game->doors[i].offset < 0)
			game->map.layout[(int)game->doors[i].pos.y] \
								[(int)game->doors[i].pos.x] = 2;
		game->doors[i].count += game->doors[i].status;
		game->doors[i].pos.z += game->doors[i].offset;
		if (game->doors[i].count == 0)
		{
			if (game->doors[i].offset > 0)
				game->map.layout[(int)game->doors[i].pos.y] \
					[(int)game->doors[i].pos.x] = 0;
			game->doors[i].status = 0;
			game->doors[i].offset = -game->doors[i].offset;
		}
		++i;
	}
}

void	update_door_status(t_game *game)
{
	int	i;

	i = is_near_door(game, game->doors, &game->pos);
	if (i == -1)
		return ;
	if (game->doors[i].t < 0.9)
		return ;
	game->doors[i].status = -1;
	game->doors[i].count = 45;
}
