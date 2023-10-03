/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/10/03 14:52:11 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	draw_map(t_link *ln, t_vec2d *idx_map, t_vec2d	*idx_draw, void *area)
{
	if (idx_map->y == ((int)ln->pos->y) - (MINIMAP_SIZE - 1)
		|| idx_map->x == ((int)ln->pos->x) - (MINIMAP_SIZE - 1)
		|| idx_map->y == ((int)ln->pos->y) + (MINIMAP_SIZE - 1)
		|| idx_map->x == ((int)ln->pos->x) + (MINIMAP_SIZE - 1))
		draw_square(ln->view, *idx_draw, *(int *) area, WHITE);
	else if (idx_map->y < 0 || idx_map->x < 0)
		draw_square(ln->view, *idx_draw, *(int *) area, DARK_RED);
	else
	{
		if (ln->map->layout[idx_map->y][idx_map->x] == 1)
			draw_square(ln->view, *idx_draw, *(int *) area, WHITE);
		else if (ln->map->layout[idx_map->y][idx_map->x] == -1)
			draw_square(ln->view, *idx_draw, *(int *) area, GREY);
		else
			draw_square(ln->view, *idx_draw, *(int *) area, BLACK);
		if (idx_map->x == (int)ln->pos->x && idx_map->y == (int)ln->pos->y)
			draw_square(ln->view, *idx_draw, 5, RED);
	}
}

void	ft_blur_pause(t_game *game)
{
	int		i;

	i = 0;
	pthread_mutex_lock(&game->m_queue);
	while (i < N_CHUNK)
	{
		if (add_job(game, &game->view, &game->area[i], blur_image))
			return ;
		++i;
	}
	pthread_mutex_unlock(&game->m_queue);
	wait_job(game);
}

void	ft_change_cursor(t_game *game, int x, int y)
{
	better_mlx_mouse_hide(game->mlx.ptr, game->mlx.win, &game->cursor);
	ft_draw_img(&game->view, game->anim[1][1], x, y);
}
