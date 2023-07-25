/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/25 21:49:54 by tlegrand         ###   ########.fr       */
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
	while (i < x && i < data_thread->idx_end[0])
	{
		j = j2;
		while (j < y && j < data_thread->idx_end[1])
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
	while (i < data_thread->idx_end[0] - SEE_TH)
	{
		j = 0;
		while (j < data_thread->idx_end[1])
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


void	*routine_simple(void *data)
{
	t_display	*data_th;

	data_th = data;
	// while (get_status(data_th->m_lock, *data_th->lock) == 0)
	// {
		// sem_wait(data_th->sem_thread);
		// th_print(data_th->m_print, "start draw", data_th->id);
		display_game(data_th);
		// th_print(data_th->m_print, "end draw", data_th->id);
		// sleep(1);
		// sem_post(data_th->sem_main);
	// }
	// th_print(data_th->m_print, "QUIT", data_th->id);
	return (NULL);
}

int	update_game(t_game *game)
{
	int	i;

	if (game->pause == 1)
		return (0);
	view_update_pos(game);
	view_update_dir_key(game);
	view_update_dir_mouse(game);
	// th_print(&game->m_print, "start launching th", 0);

	i = 0;
	while (i < N_THREAD)
	{
		if (pthread_create(&game->pid[i], NULL, routine_simple, &game->th[i]))
			dprintf(2, " ER THR\n");
		++i;
	}
	// th_print(&game->m_print, "waiting for Th", 0);
	i = -1;
	while (++i < N_THREAD)
		pthread_join(game->pid[i], NULL);


	// i = -1;
	// while (++i < N_THREAD)
	// 	sem_post(&game->sem_thread);
	// i = -1;
	// while (++i < N_THREAD)
	// 	sem_wait(&game->sem_main);
	// th_print(&game->m_print, "Th locked\n", 0);


	draw_map(game, MINIMAP_SIZE);
	ft_printf_fps(1);
	// sleep(1);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	return (0);
}
