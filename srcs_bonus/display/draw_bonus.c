/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:44 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/20 15:32:50 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	draw_square(t_game *game, int size, t_vec2d pos, int color)
{
	int	i;
	int	j;
	int	tmp;

	i = pos.y + size;
	j = pos.x + size;
	tmp = pos.x;
	while (pos.y < i)
	{
		pos.x = tmp;
		while (pos.x < j)
		{
			ft_mlx_pixel_put(&game->view, pos.x, pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}

t_vec2d	s_vec2d_init(int x, int y)
{
	t_vec2d	u;

	u.x = x;
	u.y = y;
	return (u);
}

void	draw_map(t_game *game, int size)
{
	t_vec2d	idx;
	t_vec2d	idx2;

	idx = s_vec2d_init(0, 0);
	idx2 = s_vec2d_init(10, 10);
	while (idx.x < game->map.x_size)
	{
		idx.y = 0;
		while (idx.y < game->map.y_size)
		{
			if (game->map.layout[idx.y][idx.x] == 1)
				draw_square(game, size, idx2, WHITE);
			else if (game->map.layout[idx.y][idx.x] == 0)
				draw_square(game, size, idx2, BLACK);
			else if (game->map.layout[idx.y][idx.x] == -1)
				draw_square(game, size, idx2, GREY);
			if (idx.x == (int)game->pos.x && idx.y == (int)game->pos.y)
				draw_square(game, 5, idx2, RED);
			idx2.y += size;
			idx.y++;
		}
		idx2.y = 10;
		idx2.x += size;
		idx.x++;
	}
}
