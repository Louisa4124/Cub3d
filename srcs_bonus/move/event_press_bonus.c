/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_press_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:41:10 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/17 13:41:14 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	pause_in(t_game *game)
{
	better_mlx_mouse_show(game->mlx.ptr, game->mlx.win, &game->cursor);
	ft_blur_pause(game);
	game->view_data_cpy = ft_memcpy(game->view_data_cpy, game->view.addr, \
		game->view.height * game->view.ll);
	game->pause = 6;
}

void	pause_off(t_game *game)
{
	better_mlx_mouse_hide(game->mlx.ptr, game->mlx.win, &game->cursor);
	mlx_mouse_move(game->mlx.ptr, game->mlx.win, game->mlx.win_width >> 1, \
		game->mlx.win_height >> 1);
	game->pause = 0;
}

static void	event_press_action(int keycode, t_game *game)
{
	if (keycode == KEY_SPACE)
		game->jump = 1;
	else if (keycode == KEY_P && game->pause == 0)
		pause_in(game);
	else if (keycode == KEY_P && game->pause == 6)
		pause_off(game);
	else if (keycode == KEY_ENTER && game->pause == 2)
		game->pause = 4;
	else if (keycode == KEY_E)
		update_door_status(game);
}

int	event_press(int keycode, t_game *game)
{
	if (keycode == 53 || keycode == KEY_ESCAPE)
		close_event(game);
	else if (keycode == KEY_W)
		game->bit_key |= BFLAG_W;
	else if (keycode == KEY_UP)
		game->bit_key |= BFLAG_UP;
	else if (keycode == KEY_S)
		game->bit_key |= BFLAG_S;
	else if (keycode == KEY_DOWN)
		game->bit_key |= BFLAG_DOWN;
	else if (keycode == KEY_A)
		game->bit_key |= BFLAG_A;
	else if (keycode == KEY_D)
		game->bit_key |= BFLAG_D;
	else if (keycode == KEY_RIGHT)
		game->bit_key |= BFLAG_RIGHT;
	else if (keycode == KEY_LEFT)
		game->bit_key |= BFLAG_LEFT;
	else
		event_press_action(keycode, game);
	return (0);
}

int	event_unpress(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->bit_key ^= BFLAG_W;
	else if (keycode == KEY_UP)
		game->bit_key ^= BFLAG_UP;
	else if (keycode == KEY_S)
		game->bit_key ^= BFLAG_S;
	else if (keycode == KEY_DOWN)
		game->bit_key ^= BFLAG_DOWN;
	else if (keycode == KEY_A)
		game->bit_key ^= BFLAG_A;
	else if (keycode == KEY_D)
		game->bit_key ^= BFLAG_D;
	else if (keycode == KEY_RIGHT)
		game->bit_key ^= BFLAG_RIGHT;
	else if (keycode == KEY_LEFT)
		game->bit_key ^= BFLAG_LEFT;
	return (0);
}
