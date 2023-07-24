/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/24 22:41:37 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp >> 3));
	*(unsigned int *) dst = color;
}

static void	ft_resolution(t_display *data_thread, int i, int j, int color)
{
	int	x;
	int	y;
	int	j2;

	x = i + RESOLUTION;
	y = j + RESOLUTION;
	j2 = j;
	while (i < x && i <= data_thread->idx_end[0])
	{
		j = j2;
		while (j < y && j <= data_thread->idx_end[1])
		{
			ft_mlx_pixel_put(data_thread->view, j, i, color);
			++j;
		}
		++i;
	}
}

void	ft_display_menu(t_game *game)
{
	unsigned int	*image_data;

	game->pause = 1;
	image_data = (unsigned int *)game->view.addr;
	blur_image(&game->view, image_data);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->button.id, 350, \
		100);
}

void	display_game(t_display *data_thread)
{
	int		i;
	int		j;

	i = data_thread->idx_start;
	while (i <= data_thread->idx_end[0])
	{
		j = 0;
		while (j <= data_thread->idx_end[1])
		{
			if (i > 10 && i < (data_thread->map->y_size * MINIMAP_SIZE) + 10 && j > 10 && \
				j < (data_thread->map->x_size * MINIMAP_SIZE) + 10)
			{
				j += RESOLUTION;
				continue ;
			}
			data_thread->tmp_rays = ft_rotate_vec_z(ft_rotate_vec_x(data_thread->rays[i][j], \
				*data_thread->angle_x), *data_thread->angle_z);
			data_thread->close_t = 0;
			ft_resolution(data_thread, i, j, switch_plan_algo(data_thread));
			j += RESOLUTION;
		}
		i += RESOLUTION;
	}
}


int	update_game(t_game *game)
{
	int	i;

	if (game->pause == 1)
		return (0);

	view_update_pos(game);
	view_update_dir_key(game);
	view_update_dir_mouse(game);
	i = -1;
	while (++i < N_THREAD)
		sem_post(&game->sem_thread);
	dprintf(2, " waiting for Th\n");
	i = -1;
	while (++i < N_THREAD)
		sem_wait(&game->sem_main);
	dprintf(2, " Th locked\n");


	draw_map(game, MINIMAP_SIZE);
	ft_printf_fps(1);
	sleep(1);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	return (0);
}
