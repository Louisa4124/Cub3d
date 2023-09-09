/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:59 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/09 12:44:37 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	close_event(t_game *game)
{
	ft_clean_exit(game, EXIT_SUCCESS);
	return (0);
}

int	event_pause(int button, int x, int y, t_game *game)
{
	(void)button;
	if (x < 0 || y < 0 || x > game->mlx.win_width || y > game->mlx.win_height)
		return (-1);
	if (game->pause == 5)
		event_menu(x, y, game);
	if (game->pause == 1 || game->pause == 6)
	{
		if (((x > 50 && x < 280) && (y > 1000 && y < 1050)) && game->pause == 1)
			return (game->pause = 5, 0);
		if (((x > 50 && x < 280) && (y > 1000 && y < 1050)) && game->pause == 6)
			return (game->pause = 0, 0);
		event_settings(x, y, game);
	}
	return (0);
}

int	event_settings(int x, int y, t_game *game)
{
	event_resolution(x, y, game);
	event_sensitivity(x, y, game);
	event_luminosity(x, y, game);
	return (0);
}

int	event_menu(int x, int y, t_game *game)
{
	if (((x > 1500 && x < 1530) && (y > 640 && y < 675)) && game->player == 1)
		game->player = 2;
	else if (((x > 1500 && x < 1530) && (y > 640 && y < 675))
		&& game->player == 2)
		game->player = 3;
	else if (((x > 1500 && x < 1530) && (y > 640 && y < 675))
		&& game->player == 3)
		game->player = 1;
	else if (((x > 1235 && x < 1260) && (y > 640 && y < 675))
		&& game->player == 3)
		game->player = 2;
	else if (((x > 1235 && x < 1260) && (y > 640 && y < 675))
		&& game->player == 2)
		game->player = 1;
	else if (((x > 1235 && x < 1260) && (y > 640 && y < 675))
		&& game->player == 1)
		game->player = 3;
	if ((x > 300 && x < 490) && (y > 550 && y < 590))
		return (game->pause = 7, 0);
	else if ((x > 330 && x < 470) && (y > 650 && y < 680))
		return (game->pause = 3, 0);
	else if ((x > 360 && x < 430) && (y > 745 && y < 780))
		return (close_event(game), 0);
	return (0);
}
