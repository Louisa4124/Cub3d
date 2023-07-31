/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/31 16:43:35 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp >> 3));
	*(unsigned int *) dst = color;
}

static void	ft_resolution(t_display *data, int i, int j, int color)
{
	int	x;
	int	y;
	int	j2;

	x = i + *data->resolution;
	y = j + *data->resolution;
	j2 = j;
	while (i < x && i < data->idx_end[0])
	{
		j = j2;
		while (j < y && j < data->idx_end[1])
		{
			ft_mlx_pixel_put(data->view, j, i, color);
			++j;
		}
		++i;
	}
}

void	ft_blur_pause(t_game *game)
{
	game->pause = 3;
	thread_do(game, blur_image);
	// int	i = -1;
	// while (++i < N_THREAD)
	// 	blur_image(&game->th[i]);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
}

void	ft_display_pause(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	// ft_draw_img(game, game->animation[27], 0, 0);
	// if ((x > 470 && x < 600) && (y > 380 && y < 405))
	// 	ft_draw_img(game, game->animation[28], 0, 0);
	// if ((x > 460 && x < 620) && (y > 450 && y < 480))
	// 	ft_draw_img(game, game->animation[29], 0, 0);
	// if ((x > 500 && x < 570) && (y > 530 && y < 555))
	// 	ft_draw_img(game, game->animation[30], 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
}

void    ft_display_menu(t_game *game)
{
	static int	i = 0;
	int			x;
	int			y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	if (game->ms >= 0.025)
	{
		i++;
		game->ms -= 0.025;
	}
	if (i >= 13)
		i = 0;
	ft_draw_img(&game->view, game->anim[0][i], 0, 0);
	ft_draw_img(&game->view, game->anim[0][13], 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
}

void    ft_display_fly_menu(t_game *game)
{
	static int y = 0;

	if (game->ms >= 0.004)
	{
		y -= 10;
		game->ms -= 0.004;
	}
	ft_draw_img(&game->view, game->anim[0][14], 0, 0);
	ft_draw_img(&game->view, game->anim[0][13], 0, y);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
}

void	ft_display_settings(t_game *game)
{
	static int	i = 0;
	int			x;
	int			y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	if (game->ms >= 1)
	{
		i++;
		game->ms -= 1;
	}
	if (i >= 15)
		i = 0;
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[i].id, 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[19].id, 179, 101);
	if ((x > 310 && x < 390) && (y > 400 && y < 425))
		mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[20].id, 179, 101);
	if ((x > 480 && x < 610) && (y > 400 && y < 425))
		mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[21].id, 179, 101);
	if ((x > 715 && x < 780) && (y > 400 && y < 425))
		mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[22].id, 179, 101);
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
			j += *data->resolution;
		}
		i += *data->resolution;
	}
	return (NULL);
}

int	update_game(t_game *game)
{
	if (game->pause == 4)
		ft_display_fly_menu(game);
	if (game->pause == 3)
		ft_display_pause(game);
	if (game->pause == 2)
		ft_display_menu(game);
	if (game->pause == 1)
		ft_display_settings(game);
	if (game->pause == 0)
	{
		view_update_pos(game);
		view_update_dir_key(game);
		view_update_dir_mouse(game);
		thread_do(game, display_game);
		draw_map(game, MINIMAP_SIZE);
		mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
			game->view.id, 0, 0);
	}
	ft_printf_fps(0);
	game->ms += 0.0015;
	return (0);
}
