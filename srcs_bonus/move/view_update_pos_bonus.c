/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_update_pos_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:44 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/05 19:08:34 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	ft_in_wall(t_map *map, int x, int y)
{
	if (x > map->x_size || y > map->y_size)
		return (0);
	if (x < 0 || y < 0)
		return (0);
	if (map->layout[y][x] == 1)
		return (1);
	return (0);
}

int	ft_hit_wall(t_game *game, float x, float y)
{
	if (ft_in_wall(&game->map, x - 0.1, y + 0.1)
		|| ft_in_wall(&game->map, x + 0.1, y + 0.1)
		|| ft_in_wall(&game->map, x - 0.1, y - 0.1)
		|| ft_in_wall(&game->map, x + 0.1, y - 0.1))
		return (1);
	return (0);
}

void	view_update_pos_vertical(t_game *game, int flag, t_vec3d dir, \
	t_vec3d new_pos)
{
	if ((flag & BFLAG_W) && (flag & BFLAG_S))
		return ;
	if (flag & BFLAG_W)
	{
		new_pos = math_vec_op(new_pos, dir, '+');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = new_pos;
	}
	if (flag & BFLAG_S)
	{
		new_pos = math_vec_op(new_pos, dir, '-');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = new_pos;
	}
}

void	view_update_pos_lateral(t_game *game, int flag, t_vec3d dir, \
	t_vec3d new_pos)
{
	t_vec3d	z_axis;

	if ((flag & BFLAG_A) && (flag & BFLAG_D))
		return ;
	z_axis = (t_vec3d){0, 0, 1};
	if (flag & BFLAG_A)
	{
		new_pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '+');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = new_pos;
	}
	if (flag & BFLAG_D)
	{
		new_pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '-');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = new_pos;
	}
}

void	view_update_pos(t_game *game)
{
	int		bitflag;
	t_vec3d	new_pos;
	t_vec3d	dir;

	bitflag = game->bit_key;
	new_pos = game->pos;
	dir = ft_rotate_vec_z((t_vec3d){0, -DIR_OFFSET, 0}, game->angle_z);
	view_update_pos_vertical(game, bitflag, dir, new_pos);
	view_update_pos_lateral(game, bitflag, dir, new_pos);
}
