/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_igs_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:39:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/21 13:54:24 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static t_vec3d	find_pos_igs(t_map map)
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
		if (ft_randuint(1, map.y_size - 2, &y)
			|| ft_randuint(1, map.x_size - 2, &x))
		{
			ft_putstr_fd("Error\nCan't generate random pos\n", 2);
			return ((t_vec3d){0, 0, 0});
		}
		pos.y = y + 0.5;
		pos.x = x + 0.5;
	}
	return (pos);
}

int	init_igs(t_game *game, t_igs *igs)
{
	if (N_IGS <= 0 || game->map.x_size < 5 || game->map.y_size < 5)
		return (0);
	igs[0].pos = find_pos_igs(game->map);
	igs[1].pos = find_pos_igs(game->map);
	if (game->player == 1)
	{
		igs[0].sp = &game->sprite[2];
		igs[1].sp = &game->sprite[1];
	}
	else if (game->player == 2)
	{
		igs[0].sp = &game->sprite[0];
		igs[1].sp = &game->sprite[1];
	}
	else if (game->player == 3)
	{
		igs[0].sp = &game->sprite[0];
		igs[1].sp = &game->sprite[2];
	}
	if (pthread_mutex_init(&game->igs[0].m_ms, NULL))
		return (ft_putstr_fd("Error\nMutex init igs failed\n", 2), 1);
	if (pthread_mutex_init(&game->igs[1].m_ms, NULL))
		return (ft_putstr_fd("Error\nMutex init igs failed\n", 2), 1);
	return (0);
}
