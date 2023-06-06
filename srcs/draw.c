/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:44 by lboudjem          #+#    #+#             */
/*   Updated: 2023/06/06 15:55:19 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_draw_square_black(t_game *game, int size, int x, int y)
{
	int i;
	int j;
	int tmp;

	i = x + size;
	j = y + size;
	tmp = y;
	while (x < i)
	{
		y = tmp;
		while (y < j)
		{
			my_mlx_pixel_put(&game->view, y, x, BLACK);
			y++;
		}
		x++;
	}
}

void	ft_draw_square_white(t_game *game, int size, int x, int y)
{
	int i;
	int j;
	int tmp;

	i = x + size;
	j = y + size;
	tmp = y;
	while (x < i)
	{
		y = tmp;
		while (y < j)
		{
			my_mlx_pixel_put(&game->view, y, x, WHITE);
			y++;
		}
		x++;
	}
}

void	ft_draw_pos(t_game *game, int size, int x, int y)
{
	int i;
	int j;
	int tmp;

	i = x + size;
	j = y + size;
	tmp = y;
	while (x < i)
	{
		y = tmp;
		while (y < j)
		{
			my_mlx_pixel_put(&game->view, y, x, RED);
			y++;
		}
		x++;
	}
}

void	drawMap2D(t_game *game, int size)
{
	int x = 0;
	int y = 0;
	int x1 = 10;
	int y1 = 10;

	while (x < game->map.x_size)
	{
		y = 0;
		while (y < game->map.y_size)
		{
			if (game->map.layout[y][x] == 1)
				ft_draw_square_white(game, size, y1, x1);
			else if (game->map.layout[y][x] == 0)
				ft_draw_square_black(game, size, y1, x1);
			else
				;
			if (x == (int)game->pos.x && y == (int)game->pos.y)
				ft_draw_pos(game, 5, y1, x1);
			y1 += size;
			y++;
		}
		y1 = 10;
		x1 += size;
		x++;
	}
}
