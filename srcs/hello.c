/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:53:55 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/16 16:00:22 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	game_select(t_game *game)
{
	int	xres;
	int	yres;

	mlx_get_screen_size(game->mlx.ptr, &xres, &yres);
	printf("size res :%dx%d\n", xres, yres);
}
