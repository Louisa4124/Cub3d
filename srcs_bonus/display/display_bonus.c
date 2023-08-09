/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/09 17:41:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	ft_resolution(t_tmp *data, int i, int j, int color)
{
	int	max_y;
	int	max_x;
	int	j_start;

	max_y = i + *data->link->resolution;
	max_x = j + *data->link->resolution;
	j_start = j;
	// color = darken_color(color, data->close_t, *data->link->light);
	while (i < max_y && i < data->area->end_y)
	{
		j = j_start;
		while (j < max_x && j < data->area->end_x)
		{
			ft_mlx_pixel_put(data->link->view, j, i, color);
			++j;
		}
		++i;
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
	mlx_mouse_hide(game->mlx.ptr, game->mlx.win);
	ft_draw_img(&game->view, game->anim[1][1], x, y);
}

void	ft_display_players(t_game *game)
{
	static int	y = -1100;
	static int	x = 1100;
	static int	z = 1100;

	if (game->ms >= 0.003 && y < 0)
	{
		x -= 10;
		y += 10;
		z -= 10;
		game->ms -= 0.003;
		ft_draw_img(&game->view, game->anim[0][0], 0, 0);
		ft_draw_img(&game->view, game->anim[0][6], 0, y);
		ft_draw_img(&game->view, game->anim[0][5], 0, x);
		ft_draw_img(&game->view, game->anim[0][7], z, 0);
	}
	if (y == 0)
		game->pause = 5;
}

void	display_map(void *ptr, void *area)
{
	t_link	*ln;
	t_vec2d	idx_map;
	t_vec2d	idx_draw;

	ln = ptr;
	idx_map.x = -1;
	idx_draw.x = 10;
	while (++idx_map.x < ln->map->x_size)
	{
		idx_map.y = -1;
		idx_draw.y = 10;
		while (++idx_map.y < ln->map->y_size)
		{
			if (ln->map->layout[idx_map.y][idx_map.x] == 1)
				draw_square(ln->view, idx_draw, *(int *) area, WHITE);
			else if (ln->map->layout[idx_map.y][idx_map.x] == 0)
				draw_square(ln->view, idx_draw, *(int *) area, BLACK);
			else if (ln->map->layout[idx_map.y][idx_map.x] == -1)
				draw_square(ln->view, idx_draw, *(int *) area, GREY);
			if (idx_map.x == (int)ln->pos->x && idx_map.y == (int)ln->pos->y)
				draw_square(ln->view, idx_draw, 5, RED);
			idx_draw.y += *(int *) area;
		}
		idx_draw.x += *(int *) area;
	}
}

static int	is_in_minimap(t_link *link, int i, int *j)
{
	int	max;

	max = link->map->x_size * *link->mm_size + 10;
	if (i > 10 && i < link->map->y_size * *link->mm_size + 10 
		&& *j > 10 && *j < max)
	{
		*j = max;
		return (1);
	}
	return (0);
}

void	display_game(void *ptr, void *area)
{
	t_tmp		data;
	int			i;
	int			j;

	data.area = area;
	data.link = ptr;
	// update_igs_plane(data.link->igs, *data.link->pos);
	i = data.area->start_y;
	while (i < data.area->end_y)
	{
		j = data.area->start_x;
		while (j < data.area->end_x)
		{
			if (is_in_minimap(data.link, i, &j))
				continue ;
			data.rays = ft_rotate_vec_z(ft_rotate_vec_x(data.link->rays[i][j], \
				*data.link->angle_x), *data.link->angle_z);
			data.close_t = 0;
			ft_resolution(&data, i, j, switch_plan_algo(&data));
			j += *data.link->resolution;
		}
		i += *data.link->resolution;
	}
}

void	ft_transition(t_game *game)
{
	static int	x = 0;

	if (game->ms >= 0.001 && x >= -WIDTH)
		x -= 40;
	ft_draw_img(&game->view, game->anim[0][13], x, 0);
}

int	update_game(t_game *game)
{
	if (game->pause == 7)
		ft_display_launch_game(game);
	// if (game->pause == 6)
	// 	ft_display_load(game);
	if (game->pause == 5)
		ft_display_select_menu(game);
	if (game->pause == 4)
		ft_display_fly_menu(game);
	if (game->pause == 3)
		ft_display_settings_menu(game);
	if (game->pause == 2)
		ft_display_menu(game);
	if (game->pause == 1)
		ft_select_settings(game);
	if (game->pause == 0)
	{
		view_update_pos(game);
		view_update_dir_key(game);
		update_igs_plane(game->igs, game->pos);
		send_frame_job(game);
		wait_job(game);
		animation_fire(game);
		ft_transition(game);
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	update_igs_time(game->igs);
	if (game->pause != 3)
		game->ms += 0.0015;
	ft_printf_fps(DEBUG);
	return (0);
}
