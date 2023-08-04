/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:59 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/04 12:42:13 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	event_press(int keycode, t_game *game)
{
	//printf("key = %d\n", keycode);
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
	else if (keycode == KEY_P && game->pause == 0)
		ft_blur_pause(game);
	else if (keycode == KEY_P && game->pause == 3)
		game->pause = 0;
	else if (keycode == KEY_ENTER && game->pause == 2)
		game->pause = 4;
	return (0);
}

int	event_pause(int button, int x, int y, t_game *game)
{
	(void)button;
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	if (x < 0 || y < 0 || x > game->mlx.win_width || y > game->mlx.win_height)
		return (-1);
	if (game->pause == 5)
		event_menu(x, y, game);
	if (game->pause == 1)
		event_settings(x, y, game);
	if (game->pause == 3)
	{
		if ((x > 470 && x < 600) && (y > 380 && y < 405))
			return (game->pause = 0, 0);
		if ((x > 460 && x < 620) && (y > 450 && y < 480))
			return (0);
		if ((x > 500 && x < 570) && (y > 530 && y < 555))
			return (close_event(game), 0);
	}
	return (0);
}

int	event_settings(int x, int y, t_game *game)
{
	if ((x > 310 && x < 390) && (y > 400 && y < 425))
	{
		game->resolution = 1;
		game->pause = 2;
		ft_display_menu(game);
		return (0);
	}
	if ((x > 480 && x < 610) && (y > 400 && y < 425))
	{
		game->resolution = 2;
		game->pause = 2;
		ft_display_menu(game);
		return (0);
	}
	if ((x > 715 && x < 780) && (y > 400 && y < 425))
	{
		game->resolution = 3;
		game->pause = 2;
		ft_display_menu(game);
		return (0);
	}
	return (0);
}

int	event_menu(int x, int y, t_game *game)
{
	if ((x > 550 && x < 650) && (y > 650 && y < 920))
	{
		game->player = 1;
		game->pause = 6;
	}
	else if ((x > 950 && x < 1050) && (y > 710 && y < 920))
	{
		game->player = 2;
		game->pause = 6;\
	}
	else if ((x > 1320 && x < 1410) && (y > 670 && y < 920))
	{
		game->player = 3;
		game->pause = 6;
	}
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

int	close_event(t_game *game)
{
	ft_clean_exit(game, EXIT_SUCCESS);
	return (0);
}
