/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_in_game_sprite_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:39:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/09 12:41:36 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	is_igs_here(t_vec3d pos, t_igs *igs)
{
	int	i;

	i = 0;
	while (i < N_IGS)
	{
		if (pos.x == igs[i].pos.x && pos.y == igs[i].pos.y)
			return (1);
		++i;
	}
	return (0);
}

static t_vec3d	find_pos_igs(t_map map, t_igs *igs)
{
	t_vec3d	pos;
	int		y;
	int		x;
	int		i;

	i = 0;
	y = 0;
	x = 0;
	while (map.layout[y][x] != 0 && ++i < 51)
	{
		if (ft_randuint(1, map.y_size - 1, &y) 
			|| ft_randuint(1, map.x_size - 1, &x))
		{
			ft_putendl_fd("Error\nCan't generate random pos\n", 2);
			return ((t_vec3d){0, 0, 0});
		}
		pos.y = y + 0.5;
		pos.x = x + 0.5;
		if (is_igs_here(pos, igs) != 0)
			break ;
		dprintf(2, "rand try %d\n", i);
	}
	return (pos);
}

void	init_igs(t_game *game, t_igs *igs)
{
	if (N_IGS <= 0)
		return ;
	igs[0].pos = find_pos_igs(game->map, igs);
	igs[0].sp = &game->sprite[3];
	dprintf(2, "pos igs rand %f %f\n", igs[0].pos.x, igs[0].pos.y);
	if (N_IGS <= 1)
		return ;
	igs[1].pos = find_pos_igs(game->map, igs);
	igs[1].sp = &game->sprite[4];
	dprintf(2, "pos igs rand %f %f\n", igs[1].pos.x, igs[1].pos.y);
}
