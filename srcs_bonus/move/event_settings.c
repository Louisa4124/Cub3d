/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:47:45 by lboudjem          #+#    #+#             */
/*   Updated: 2023/09/17 15:59:38 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	event_resolution(int x, int y, t_game *game)
{
	if (y < 500 || y > 520)
		return ;
	if (x > 1170 && x < 1200 && game->resolution == 2)
		game->resolution = 5;
	else if (x > 1170 && x < 1200 && game->resolution == 3)
		game->resolution = 2;
	else if (x > 1170 && x < 1200 && game->resolution == 5)
		game->resolution = 3;
	else if (x > 1015 && x < 1045 && game->resolution == 2)
		game->resolution = 3;
	else if (x > 1015 && x < 1045 && game->resolution == 3)
		game->resolution = 5;
	else if (x > 1015 && x < 1045 && game->resolution == 5)
		game->resolution = 2;
}

void	event_sensitivity(int x, int y, t_game *game)
{
	if (y < 620 || y > 650)
		return ;
	if (x > 1170 && x < 1200 && game->angle_offset >= 0.000 
		&& game->angle_offset < 0.002)
		game->angle_offset = 0.003;
	else if (x > 1170 && x < 1200 && game->angle_offset >= 0.002 
		&& game->angle_offset < 0.004) 
		game->angle_offset = 0.005;
	else if (x > 1170 && x < 1200 && game->angle_offset >= 0.004)
		game->angle_offset = 0.001;
	else if (x > 1015 && x < 1045 && game->angle_offset >= 0.000 
		&& game->angle_offset < 0.002)
		game->angle_offset = 0.005;
	else if (x > 1015 && x < 1045 && game->angle_offset >= 0.002 
		&& game->angle_offset < 0.004)
		game->angle_offset = 0.001;
	else if (x > 1015 && x < 1045 && game->angle_offset >= 0.004)
		game->angle_offset = 0.003;
}

void	event_luminosity(int x, int y, t_game *game)
{
	if (y < 760 || y > 780)
		return ;
	if (x > 1170 && x < 1200 && *game->link.light >= 0.2 
		&& *game->link.light < 0.4)
		*game->link.light = 0.7;
	else if (x > 1170 && x < 1200 && *game->link.light >= 0.6 
		&& *game->link.light < 0.8)
		*game->link.light = 1;
	else if (x > 1170 && x < 1200 && *game->link.light >= 1)
		*game->link.light = 0.3;
	else if (x > 1015 && x < 1045 && *game->link.light >= 0.2 
		&& *game->link.light < 0.4)
		*game->link.light = 1;
	else if (x > 1015 && x < 1045 && *game->link.light >= 0.6 
		&& *game->link.light < 0.8)
		*game->link.light = 0.3;
	else if (x > 1015 && x < 1045 && *game->link.light >= 1)
		*game->link.light = 0.7;
}
