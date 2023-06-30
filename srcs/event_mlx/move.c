/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:44 by tlegrand          #+#    #+#             */
/*   Updated: 2023/06/30 16:32:29 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// TODO: verifier que x et y sont dans la map
int	ft_in_wall(t_game *game, int x, int y)
{
	if (x >= 0 && y >= 0 && game->map.layout[y][x] == 1)
		return (1);
	return (0);
}

int	ft_hit_wall(t_game *game, float x, float y)
{
	if (ft_in_wall(game, x - 0.1, y + 0.1)
		|| ft_in_wall(game, x + 0.1, y + 0.1)
		|| ft_in_wall(game, x - 0.1, y - 0.1)
		|| ft_in_wall(game, x + 0.1, y - 0.1))
		return (1);
	return (0);
}

int	ft_move(t_game *game)
{
	t_vec3d	z_axis;
	t_vec3d	dir;
	t_vec3d	new_pos;

	z_axis = s_vec3d_init(0, 0, 1);
	new_pos = s_vec3d_init(game->pos.x, game->pos.y, game->pos.z);
	dir = ft_rotate_vec_z(s_vec3d_init(0, -DIR_OFFSET, 0), game->angle_z);
	if (game->bit_key & BFLAG_W)
	{
		new_pos = math_vec_op(new_pos, dir, '+');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = math_vec_op(game->pos, dir, '+');
	}
	if (game->bit_key & BFLAG_S)
	{
		new_pos = math_vec_op(new_pos, dir, '-');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = math_vec_op(game->pos, dir, '-');
	}
	if (game->bit_key & BFLAG_A)
	{
		new_pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '+');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = math_vec_op(game->pos, math_vec_op(dir, z_axis, '^'), '+');
	}
	if (game->bit_key & BFLAG_D)
	{
		new_pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '-');
		if (!ft_hit_wall(game, new_pos.x, new_pos.y))
			game->pos = math_vec_op(game->pos, math_vec_op(dir, z_axis, '^'), '-');
	}
	if (game->bit_key & BFLAG_RIGHT)
		game->angle_z += ANG_OFFSET;
	if (game->bit_key & BFLAG_LEFT)
		game->angle_z -= ANG_OFFSET;
	if (game->bit_key & BFLAG_UP && game->angle_x > -0.5)
		game->angle_x -= ANG_OFFSET;
	if (game->bit_key & BFLAG_DOWN && game->angle_x < 0.5)
		game->angle_x += ANG_OFFSET;
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	else if (game->angle_z <= -PI * 2)
		game->angle_z += PI * 2;
	return (0);
}

void	view_rotate(t_game *game)
{
	int	x_quarter;
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	x_quarter = game->mlx.win_width >> 2;
	if (x >= 0 && x < x_quarter)
	{
		game->angle_z -= 0.07;
		game->dir = ft_rotate_vec_z(game->dir, -0.007);
	}
	else if (x > x_quarter * 3 && x <= game->mlx.win_width)
	{
		game->angle_z += 0.07;
		game->dir = ft_rotate_vec_z(game->dir, 0.007);
	}
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	else if (game->angle_z <= -PI * 2)
		game->angle_z += PI * 2;
}
