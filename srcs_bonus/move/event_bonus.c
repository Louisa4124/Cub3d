/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:43:59 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/04 17:46:44 by tlegrand         ###   ########.fr       */
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
	if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) && game->resolution == 2)
		game->resolution = 3;
	else if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) && game->resolution == 3)
		game->resolution = 5;
	else if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) && game->resolution == 5)
		game->resolution = 2;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) && game->resolution == 2)
		game->resolution = 5;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) && game->resolution == 3)
		game->resolution = 2;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) && game->resolution == 5)
		game->resolution = 3;
	
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


