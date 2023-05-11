/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:14:24 by lboudjem          #+#    #+#             */
/*   Updated: 2023/05/11 16:48:33 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void	ft_move_next(int keycode, t_game *game)
{	
	if (keycode == EVENT_A)
	{
		if (game->map[(int)(game->pos.y - sin(game->angle_z) * 0.20)]
			[(int)(game->pos.x - cos(game->angle_z) * 0.20)] != '1')
		{
			game->pos.x -= cos(game->angle_z) * 0.1;
			game->pos.y -= sin(game->angle_z) * 0.1;
		}
	}
	if (keycode == EVENT_D)
	{
		if (game->map[(int)(game->pos.y + sin(game->angle_z) * 0.20)]
			[(int)(game->pos.x + cos(game->angle_z) * 0.20)] != '1')
		{
			game->pos.x += cos(game->angle_z) * 0.1;
			game->pos.y += sin(game->angle_z) * 0.1;
		}
	}
}
void	ft_move(int keycode, t_game *game)
{
	if (keycode == EVENT_W)
	{
		if (game->map[(int)(game->pos.y - cos(game->angle_z) * 0.20)]
			[(int)(game->pos.x + sin(game->angle_z) * 0.20)] != '1')
		{
			game->pos.x += sin(game->angle_z) * 0.1;
			game->pos.y -= cos(game->angle_z) * 0.1;
		}
	}
	if (keycode == EVENT_S)
	{
		if (game->map[(int)(game->pos.y + cos(game->angle_z) * 0.20)]
			[(int)(game->pos.x - sin(game->angle_z) * 0.20)] != '1')
		{
			game->pos.x -= sin(game->angle_z) * 0.1;
			game->pos.y += cos(game->angle_z) * 0.1;
		}
	}
	ft_move_next(keycode, game);
}

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
