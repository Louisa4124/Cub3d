/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/31 13:16:26 by tlegrand         ###   ########.fr       */
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

int	thread_do(t_game *game, void *(f)(void *))
{
	int	i;

	i = -1;
	i = -1;
	while (++i < N_THREAD)
	{
		if (pthread_create(&game->pid[i], NULL, f, &game->th[i]))
			dprintf(2, " ER THR\n");
	}
	while (--i >= 0)
		pthread_join(game->pid[i], NULL);
	return (0);
}

void	ft_display_menu(t_game *game)
{
	game->pause = 1;
	// thread_do(game, blur_image);
	int	i = -1;
	while (++i < N_THREAD)
		blur_image(&game->th[i]);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->button.id, 350, \
		100);
}

void	*display_game(void *ptr)
{
	t_display	*data;
	int			i;
	int			j;

	data = ptr;
	i = data->idx_start;
	while (i < data->idx_end[0] - SEE_TH)
	{
		j = 0;
		while (j < data->idx_end[1])
		{
			if (i > 10 && i < (data->map->y_size * MINIMAP_SIZE) + 10 && \
				j > 10 && j < (data->map->x_size * MINIMAP_SIZE) + 10)
			{
				j = (data->map->x_size * MINIMAP_SIZE) + 10;
				continue ;
			}
			data->tmp_rays = ft_rotate_vec_z(ft_rotate_vec_x(data->rays[i][j], \
				*data->angle_x), *data->angle_z);
			data->close_t = 0;
			ft_resolution(data, i, j, switch_plan_algo(data));
			j += RESOLUTION;
		}
		i += RESOLUTION;
	}
	return (NULL);
}

int	update_game(t_game *game)
{
	if (game->pause == 1)
		return (0);
	view_update_pos(game);
	view_update_dir_key(game);
	view_update_dir_mouse(game);
	thread_do(game, display_game);
	draw_map(game, MINIMAP_SIZE);
	ft_printf_fps(1);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	return (0);
}
