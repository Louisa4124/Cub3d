/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:59 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/22 01:29:49 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

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
	else if (keycode == KEY_P && game->pause == 0)
		ft_display_menu(game);
	else if (keycode == KEY_P && game->pause == 1)
		game->pause = 0;
	return (0);
}

int	event_pause(int button, int x, int y, t_game *game)
{
    (void)button;
	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	if (x < 0 || y < 0 || x > game->mlx.win_width || y > game->mlx.win_height)
		return (-1);
    if (game->settings == 0)
    {   
        if ((x > 460 && x < 631) && (y > 322 && y < 376))
        {
            game->pause = 0;
            return (0);
        }
        if ((x > 460 && x < 628) && (y > 450 && y < 510))
        {
            close_event(game);
            return (0);
        }
        if ((x > 677 && x < 730) && (y > 528 && y < 573))
        {
            ft_display_settings(game);
            return (0);
        }
    }
    if (game->settings == 1)
        event_settings(button, x, y, game);
	return (0);
}

int	event_settings(int button, int x, int y, t_game *game)
{
    (void)button;
    if ((x > 385 && x < 530) && (y > 519 && y < 570))
    {
        game->settings = 0;
        ft_display_menu(game);
        return (0);
    }
    if ((x > 390 && x < 480) && (y > 375 && y < 410))
    {
        game->resolution = 1;
        return (0);
    }
    if ((x > 500 && x < 595) && (y > 375 && y < 410))
    {
        game->resolution = 2;
        return (0);
    }
    if ((x > 620 && x < 715) && (y > 375 && y < 410))
    {
        game->resolution = 3;
        return (0);
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
