/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:59 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/07 17:57:08 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	pause_in(t_game *game)
{
	game->pause = 3;
	mlx_mouse_show(game->mlx.ptr, game->mlx.win);
	ft_blur_pause(game);
}

void	pause_off(t_game *game)
{
	mlx_mouse_hide(game->mlx.ptr, game->mlx.win);
	mlx_mouse_move(game->mlx.ptr, game->mlx.win, game->mlx.win_width >> 1, \
		game->mlx.win_height >> 1);
	game->pause = 0;
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
	else if (keycode == KEY_P && game->pause == 0)
		pause_in(game);
	else if (keycode == KEY_P && game->pause == 3)
		pause_off(game);
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
	if (game->pause == 3)
	{
		if (((x > 50 && x < 280) && (y > 1000 && y < 1050)))
			return(game->pause = 0, 0);
		event_settings(x, y, game);
	}
	return (0);
}

int	event_settings(int x, int y, t_game *game)
{
	if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) && game->resolution == 1)
		game->resolution = 2;
	else if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) && game->resolution == 2)
		game->resolution = 4;
	else if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) && game->resolution == 4)
		game->resolution = 1;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) && game->resolution == 1)
		game->resolution = 4;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) && game->resolution == 2)
		game->resolution = 1;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) && game->resolution == 4)
		game->resolution = 2;
	
	else if (((x > 1170 && x < 1200) && (y > 620 && y < 650)) && (game->angle_offset >= 0 && game->angle_offset < 0.002))
		game->angle_offset = 0.005;
	else if (((x > 1170 && x < 1200) && (y > 620 && y < 650)) && (game->angle_offset >= 0.002 && game->angle_offset < 0.004)) 
		game->angle_offset = 0.001;
	else if (((x > 1170 && x < 1200) && (y > 620 && y < 650)) && game->angle_offset >= 0.004)
		game->angle_offset = 0.003;
	else if (((x > 1015 && x < 1045) && (y > 620 && y < 650)) && (game->angle_offset >= 0 && game->angle_offset < 0.002))
		game->angle_offset = 0.003;
	else if (((x > 1015 && x < 1045) && (y > 620 && y < 650)) && (game->angle_offset >= 0.002 && game->angle_offset < 0.004))
		game->angle_offset = 0.005;
	else if (((x > 1015 && x < 1045) && (y > 620 && y < 650)) && game->angle_offset >= 0.004)
		game->angle_offset = 0.001;

	else if (((x > 1170 && x < 1200) && (y > 760 && y < 780)) && *game->link.light >= 0 && *game->link.light < 1)
		*game->link.light = 1;
	else if (((x > 1170 && x < 1200) && (y > 760 && y < 780)) && *game->link.light >= 1 && *game->link.light < 1.4)
		*game->link.light = 1.5;
	else if (((x > 1170 && x < 1200) && (y > 760 && y < 780)) && *game->link.light >= 1.4)
		*game->link.light = 0.5;
	else if (((x > 1015 && x < 1045) && (y > 760 && y < 780)) && *game->link.light >= 0 && *game->link.light < 1)
		*game->link.light = 1.5;
	else if (((x > 1015 && x < 1045) && (y > 760 && y < 780)) && *game->link.light >= 1 && *game->link.light < 1.4)
		*game->link.light = 0.5;
	else if (((x > 1015 && x < 1045) && (y > 760 && y < 780)) && *game->link.light >= 1.4)
		*game->link.light = 1;
	return (0);
}

int	event_menu(int x, int y, t_game *game)
{
	if (((x > 1500 && x < 1530) && (y > 640 && y < 675)) && game->player == 1)
		game->player = 2;
	else if (((x > 1500 && x < 1530) && (y > 640 && y < 675)) && game->player == 2)
		game->player = 3;
	else if (((x > 1500 && x < 1530) && (y > 640 && y < 675)) && game->player == 3)
		game->player = 1;
	else if (((x > 1235 && x < 1260) && (y > 640 && y < 675)) && game->player == 3)
		game->player = 2;
	else if (((x > 1235 && x < 1260) && (y > 640 && y < 675)) && game->player == 2)
		game->player = 1;
	else if (((x > 1235 && x < 1260) && (y > 640 && y < 675)) && game->player == 1)
		game->player = 3;
	if ((x > 300 && x < 490) && (y > 550 && y < 590))
		return (game->pause = 7, 0);
	else if ((x > 330 && x < 470) && (y > 650 && y < 680))
		return (game->pause = 3, 0);
	else if ((x > 360 && x < 430) && (y > 745 && y < 780))
		return (close_event(game), 0);
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
