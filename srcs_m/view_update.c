/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:44 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/19 12:33:45 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

void	view_update_pos_vertical(t_game *game, int bitflag, t_vec3d dir, t_vec3d new_pos)
{
	if ((bitflag & BFLAG_W) && (bitflag & BFLAG_S))
		return ;
	if (bitflag & BFLAG_W)
	{
		new_pos = math_vec_op(new_pos, dir, '+');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = new_pos;
	}
	if (bitflag & BFLAG_S)
	{
		new_pos = math_vec_op(new_pos, dir, '-');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = new_pos;
	}
}

void	view_update_pos_lateral(t_game *game, int bitflag, t_vec3d dir, t_vec3d new_pos)
{
	t_vec3d	z_axis;

	if ((bitflag & BFLAG_A) && (bitflag & BFLAG_D))
		return ;
	z_axis = s_vec3d_init(0, 0, 1);
	if (bitflag & BFLAG_A)
	{
		new_pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '+');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = new_pos;
	}
	if (bitflag & BFLAG_D)
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
	dir = ft_rotate_vec_z(s_vec3d_init(0, -DIR_OFFSET, 0), game->angle_z);
	view_update_pos_vertical(game, bitflag, dir, new_pos);
	view_update_pos_lateral(game, bitflag, dir, new_pos);
}

float	pi_modulo(float z)
{
	if (z >= PI_DOUBLE)
		z -= PI_DOUBLE;
	else if (z <= -PI_DOUBLE)
		z += PI_DOUBLE;
	return (z);
}

void	view_update_dir(t_game *game)
{
	if (game->bit_key & BFLAG_RIGHT)
		game->angle_z += ANG_OFFSET_KEY;
	if (game->bit_key & BFLAG_LEFT)
		game->angle_z -= ANG_OFFSET_KEY;
	game->angle_z = pi_modulo(game->angle_z);
}
