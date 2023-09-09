/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:47:45 by lboudjem          #+#    #+#             */
/*   Updated: 2023/09/09 12:44:42 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	event_resolution(int x, int y, t_game *game)
{
	if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) 
		&& game->resolution == 2)
		game->resolution = 3;
	else if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) 
		&& game->resolution == 3)
		game->resolution = 5;
	else if (((x > 1170 && x < 1200) && (y > 500 && y < 520)) 
		&& game->resolution == 5)
		game->resolution = 2;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) 
		&& game->resolution == 2)
		game->resolution = 5;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) 
		&& game->resolution == 3)
		game->resolution = 2;
	else if (((x > 1015 && x < 1045) && (y > 500 && y < 520)) 
		&& game->resolution == 5)
		game->resolution = 3;
}

void	event_sensitivity(int x, int y, t_game *game)
{
	if (((x > 1170 && x < 1200) && (y > 620 && y < 650))
		&& (game->angle_offset >= 0 && game->angle_offset < 0.002))
		game->angle_offset = 0.005;
	else if (((x > 1170 && x < 1200) && (y > 620 && y < 650)) 
		&& (game->angle_offset >= 0.002 && game->angle_offset < 0.004)) 
		game->angle_offset = 0.001;
	else if (((x > 1170 && x < 1200) && (y > 620 && y < 650)) 
		&& game->angle_offset >= 0.004)
		game->angle_offset = 0.003;
	else if (((x > 1015 && x < 1045) && (y > 620 && y < 650)) 
		&& (game->angle_offset >= 0 && game->angle_offset < 0.002))
		game->angle_offset = 0.003;
	else if (((x > 1015 && x < 1045) && (y > 620 && y < 650)) 
		&& (game->angle_offset >= 0.002 && game->angle_offset < 0.004))
		game->angle_offset = 0.005;
	else if (((x > 1015 && x < 1045) && (y > 620 && y < 650)) 
		&& game->angle_offset >= 0.004)
		game->angle_offset = 0.001;
}

void	event_luminosity(int x, int y, t_game *game)
{
	if (((x > 1170 && x < 1200) && (y > 760 && y < 780)) 
		&& *game->link.light >= 0 && *game->link.light < 1)
		*game->link.light = 1;
	else if (((x > 1170 && x < 1200) && (y > 760 && y < 780)) 
		&& *game->link.light >= 1 && *game->link.light < 1.4)
		*game->link.light = 1.5;
	else if (((x > 1170 && x < 1200) && (y > 760 && y < 780)) 
		&& *game->link.light >= 1.4)
		*game->link.light = 0.5;
	else if (((x > 1015 && x < 1045) && (y > 760 && y < 780)) 
		&& *game->link.light >= 0 && *game->link.light < 1)
		*game->link.light = 1.5;
	else if (((x > 1015 && x < 1045) && (y > 760 && y < 780)) 
		&& *game->link.light >= 1 && *game->link.light < 1.4)
		*game->link.light = 0.5;
	else if (((x > 1015 && x < 1045) && (y > 760 && y < 780)) 
		&& *game->link.light >= 1.4)
		*game->link.light = 1;
}
