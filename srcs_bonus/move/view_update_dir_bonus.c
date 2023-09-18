/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_update_dir_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:05:38 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/18 21:24:19 by tlegrand         ###   ########.fr       */
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

int	event_mouse(int x, int y, t_game *game)
{
	float	tmp;

	if (game->pause != 0 || (x == game->mouse.x && y == game->mouse.y))
		return (0);
	if (x <= 0 || y <= 0 || x >= game->mlx.win_width - 1
		|| y >= game->mlx.win_height - 1)
	{
		mlx_mouse_move(game->mlx.ptr, game->mlx.win, game->mlx.win_width >> 1, \
		game->mlx.win_height >> 1);
		game->mouse.y = game->mlx.win_height >> 1;
		game->mouse.x = game->mlx.win_width >> 1;
		return (1);
	}
	game->angle_z = pi_modulo(game->angle_z + (x - game->mouse.x) * 0.004);
	game->mouse.x = x;
	tmp = pi_modulo(game->angle_x + (y - game->mouse.y) * 0.004);
	if (tmp < -0.5)
		tmp = -0.5;
	else if (tmp > 0.5)
		tmp = 0.5;
	game->angle_x = tmp;
	game->mouse.y = y;
	return (0);
}

int	event_mouse_reset(t_game *game)
{
	if (game->pause != 0)
		return (0);
	mlx_mouse_move(game->mlx.ptr, game->mlx.win, game->mlx.win_width >> 1, \
		game->mlx.win_height >> 1);
	game->mouse.y = game->mlx.win_height >> 1;
	game->mouse.x = game->mlx.win_width >> 1;
	return (0);
}
