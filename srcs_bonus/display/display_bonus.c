/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/04 14:53:37 by tlegrand         ###   ########.fr       */
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
	color = darken_color(color, data->close_t, *data->link->light);
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
	static float	y = -1100;
	static float	x = 1100;
	static float	z = 1100;

	if (game->ms >= 0.003 && y < 0)
	{
		x = x - (game->ms * game->ms) * 1250;
		y = y + (game->ms * game->ms) * 1250;
		z = z - (game->ms * game->ms) * 1250;
		game->ms -= 0.003;
		ft_draw_img_vel(&game->view, game->anim[0][0], 0, 0);
		ft_draw_img_vel(&game->view, game->anim[0][6], 0, y);
		ft_draw_img_vel(&game->view, game->anim[0][5], 0, x);
		ft_draw_img_vel(&game->view, game->anim[0][7], z, 0);
	}
	if ((int)y >= 0)
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

void	ft_display_settings(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	ft_draw_img(&game->view, game->blur, 0, 0);
	ft_draw_img(&game->view, game->anim[0][15], 0, 0);
	if (game->resolution == 2)
		ft_draw_img(&game->view, game->anim[0][16], 150, -30);
	else if (game->resolution == 3)
		ft_draw_img(&game->view, game->anim[0][17], 150, -30);
	else if (game->resolution == 5)
		ft_draw_img(&game->view, game->anim[0][18], 150, -30);
	if (game->angle_offset >= 0.000 && game->angle_offset < 0.002)
		ft_draw_img(&game->view, game->anim[0][18], 150, 100);
	else if (game->angle_offset >= 0.002 && game->angle_offset < 0.004)
		ft_draw_img(&game->view, game->anim[0][17], 150, 100);
	else if (game->angle_offset >= 0.004)
		ft_draw_img(&game->view, game->anim[0][16], 150, 100);
	if (*game->link.light >= 0 && *game->link.light < 1)
		ft_draw_img(&game->view, game->anim[0][16], 150, 230);
	else if (*game->link.light >= 1 && *game->link.light < 1.5)
		ft_draw_img(&game->view, game->anim[0][17], 150, 230);
	else if (*game->link.light >= 1.4)
		ft_draw_img(&game->view, game->anim[0][18], 150, 230);
	ft_settings_mouse(game, x, y);
}

void	ft_transition(t_game *game)
{
	static float	x = 0;

	if (game->ms >= 0.001 && x >= -WIDTH)
		x -= 40;
	// x = x - (game->ms * game->ms) * WIDTH;
	ft_draw_img_vel(&game->view, game->anim[0][13], x, 0);
}

void	ft_jump(t_game *game)
{
	if (game->jump == 1)
	{
		if (game->pos.z < 0.8)
			game->pos.z += (sqrt(2 * G * 0.2)) / 80 ;
		else
			game->jump = 2;
	}
	if (game->jump == 2)
	{
		if (game->pos.z > 0.5)
			game->pos.z -= (sqrt(2 * G * 0.2)) / 70;
		else
			game->jump = 0;
	}
}

int	update_game(t_game *game)
{
	if (game->pause == 7)
		ft_display_launch_game(game);
	if (game->pause == 6)
		ft_display_settings(game);
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
		update_doors_dist(game->doors, &game->pos, game->n_doors);
		update_door(game);
		send_frame_job(game);
		wait_job(game);
		animation_fire(game);
		ft_transition(game);
		ft_jump(game);
		if (is_near_door(game, game->doors, &game->pos) != -1)
			ft_animation_v(game, &game->sprite[18], (t_vec2d){670, 970}, 0.02);
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	update_igs_time(game->igs);
	if (game->pause != 6 && game->pause != 3)
		game->ms += 0.0015;
	ft_printf_fps(DEBUG);
	return (0);
}
