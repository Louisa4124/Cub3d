/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_update_dir_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:05:38 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/20 15:55:46 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

float	pi_modulo(float z)
{
	if (z >= PI_DOUBLE)
		z -= PI_DOUBLE;
	else if (z <= -PI_DOUBLE)
		z += PI_DOUBLE;
	return (z);
}

void	view_update_dir_key(t_game *game)
{
	if (game->bit_key & BFLAG_RIGHT)
		game->angle_z += ANG_OFFSET_KEY;
	if (game->bit_key & BFLAG_LEFT)
		game->angle_z -= ANG_OFFSET_KEY;
	if (game->bit_key & BFLAG_UP && game->angle_x > -0.5)
		game->angle_x -= ANG_OFFSET_KEY;
	if (game->bit_key & BFLAG_DOWN && game->angle_x < 0.5)
		game->angle_x += ANG_OFFSET_KEY;
	game->angle_z = pi_modulo(game->angle_z);
}

void	view_update_dir_mouse(t_game *game)
{
	float	tmp;
	int		mid;
	int		x;
	int		y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	if (x < 0 || y < 0 || x > game->mlx.win_width || y > game->mlx.win_height)
		return ;
	mid = game->mlx.win_width >> 1;
	x = (x - mid) >> 8;
	game->angle_z += ANG_OFFSET_MOUSE * x;
	game->angle_z = pi_modulo(game->angle_z);
	mid = game->mlx.win_height >> 1;
	y = (y - mid) >> 8;
	tmp = game->angle_x + ANG_OFFSET_MOUSE * y;
	if (tmp < -0.5 || tmp > 0.5)
		return ;
	game->angle_x = tmp;
}
