/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:44 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/03 21:41:06 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	view_update_pos(t_game *game)
{
	int		bitflag;
	t_vec3d	new_pos;
	t_vec3d	dir;
	t_vec3d	z_axis;

	bitflag = game->bit_key;
	new_pos = game->pos;
	dir = ft_rotate_vec_z(s_vec3d_init(0, -DIR_OFFSET, 0), game->angle_z);
	z_axis = s_vec3d_init(0, 0, 1);
	if (bitflag & BFLAG_W)
		game->pos = math_vec_op(new_pos, dir, '+');
	if (bitflag & BFLAG_S)
		game->pos = math_vec_op(new_pos, dir, '-');
	if (bitflag & BFLAG_A)
		game->pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '+');
	if (bitflag & BFLAG_D)
		game->pos = math_vec_op(new_pos, math_vec_op(dir, z_axis, '^'), '-');
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
