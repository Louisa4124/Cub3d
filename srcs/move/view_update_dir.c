/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_update_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:05:38 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/02 15:31:00 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
		game->angle_z += ANG_OFFSET;
	if (game->bit_key & BFLAG_LEFT)
		game->angle_z -= ANG_OFFSET;
	if (game->bit_key & BFLAG_UP && game->angle_x > -0.5)
		game->angle_x -= ANG_OFFSET;
	if (game->bit_key & BFLAG_DOWN && game->angle_x < 0.5)
		game->angle_x += ANG_OFFSET;
	game->angle_z = pi_modulo(game->angle_z);
}

void	view_update_dir_mouse(t_game *game)
{
	int	x_quarter;
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	if (x < 0 || y < 0 || x > game->mlx.win_width || y > game->mlx.win_height)
		return ;
	x_quarter = game->mlx.win_width >> 2;
	if (x < x_quarter)
	{
		game->angle_z -= 0.07;
		game->dir = ft_rotate_vec_z(game->dir, -0.007);
	}
	else if (x > x_quarter * 3)
	{
		game->angle_z += 0.07;
		game->dir = ft_rotate_vec_z(game->dir, 0.007);
	}
	game->angle_z = pi_modulo(game->angle_z);
}
