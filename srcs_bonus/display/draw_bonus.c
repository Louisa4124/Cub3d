/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:35:44 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/03 14:18:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	draw_square(t_img *img, int size, t_vec2d pos, int color)
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
			ft_mlx_pixel_put(img, pos.x, pos.y, color);
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

void	draw_map(void *ptr, t_area *area)
{
	t_link	*link;
	t_vec2d	idx;
	t_vec2d	idx2;

	link = ptr;
	(void) area;
	idx = (t_vec2d){0, 0};
	idx2 = (t_vec2d){10, 10};
	while (idx.x < link->map->x_size)
	{
		idx.y = 0;
		while (idx.y < link->map->y_size)
		{
			if (link->map->layout[idx.y][idx.x] == 1)
				draw_square(link->view, MINIMAP_SIZE, idx2, WHITE);
			else if (link->map->layout[idx.y][idx.x] == 0)
				draw_square(link->view, MINIMAP_SIZE, idx2, BLACK);
			else if (link->map->layout[idx.y][idx.x] == -1)
				draw_square(link->view, MINIMAP_SIZE, idx2, GREY);
			if (idx.x == (int)link->pos->x && idx.y == (int)link->pos->y)
				draw_square(link->view, 5, idx2, RED);
			idx2.y += MINIMAP_SIZE;
			idx.y++;
		}
		idx2.y = 10;
		idx2.x += MINIMAP_SIZE;
		idx.x++;
	}
}
