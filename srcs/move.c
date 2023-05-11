/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:14:24 by lboudjem          #+#    #+#             */
/*   Updated: 2023/05/11 14:37:10 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	key_handler(int keycode, t_game *game)
{
	ft_move(keycode, game);
	if (keycode == 65363)
		game->angle_z += 0.07;
	if (keycode == 65361)
		game->angle_z -= 0.07;
	if (keycode == 65362)
		if (game->angle_x > -0.2)
			game->angle_x -= 0.01;
	if (keycode == 65364)
		if (game->angle_x < 0.2)
			game->angle_x += 0.01;
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	if (game->angle_z <= 0)
		game->angle_z += PI * 2;
	if (keycode == EVENT_ESC)
	{
		mlx_loop_end(game->mlx.ptr);
		return (0);
	}
	return (0);
}
