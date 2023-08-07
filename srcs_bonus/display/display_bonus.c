/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/07 17:52:10 by louisa           ###   ########.fr       */
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

void	ft_display_pause(t_game *game)
{
	(void)game;
	return ;
}

void	ft_display_menu(t_game *game)
{
	ft_draw_img(&game->view, game->anim[0][0], 0, 0);
	ft_draw_img(&game->view, game->anim[0][1], 0, 0);
	ft_draw_img(&game->view, game->anim[0][2], 0, 0);
	ft_draw_img(&game->view, game->anim[0][3], 0, 0);
	ft_animation_v(game, &game->sprite[10], (t_vec2d) {670, 970}, 0.02);
	if (game->ms >= 0.02)
		game->ms -= 0.02;
}

void	ft_display_cat(t_game *game)
{
	static int	x = 20;
	static int	count = 0;

	if (count < 1)
		count += ft_animation_h(game, &game->sprite[11], (t_vec2d) {x, 985}, 0.08);
	else if (count < 4)
	{
		if (game->ms >= 0.05 && game->pause == 5)
			++x;
		count += ft_animation_h(game, &game->sprite[15], (t_vec2d) {x, 985}, 0.08);
	}
	else if (count < 5)
		count += ft_animation_h(game, &game->sprite[11], (t_vec2d) {x, 985}, 0.08);
	else if (count < 6)
		count += ft_animation_h(game, &game->sprite[14], (t_vec2d) {x, 985}, 0.08);
	else if (count < 7)
		count += ft_animation_h(game, &game->sprite[12], (t_vec2d) {x, 985}, 0.08);
	else
		ft_draw_img(&game->view, game->sprite[16].img, x, 985);
}

void	ft_change_cursor(t_game *game, int x, int y)
{
	mlx_mouse_hide(game->mlx.ptr, game->mlx.win);
	ft_draw_img(&game->view, game->anim[1][1], x, y);
}

void	ft_display_select_player(t_game *game, int x, int y)
{
	if ((x > 1500 && x < 1530) && (y > 640 && y < 675))
	{
		ft_draw_img(&game->view, game->anim[0][9], 0, 0);
		ft_change_cursor(game, x, y);
	}
	else if ((x > 1235 && x < 1260) && (y > 640 && y < 675))
	{
		ft_draw_img(&game->view, game->anim[0][8], 0, 0);
		ft_change_cursor(game, x, y);		
	}
	else if ((x > 300 && x < 490) && (y > 550 && y < 590))
	{
		ft_draw_img(&game->view, game->anim[0][10], 0, 0);
		ft_change_cursor(game, x, y);
	}
	else if ((x > 330 && x < 470) && (y > 650 && y < 680))
	{
		ft_draw_img(&game->view, game->anim[0][11], 0, 0);
		ft_change_cursor(game, x, y);
	}
	else if ((x > 360 && x < 430) && (y > 745 && y < 780))
	{
		ft_draw_img(&game->view, game->anim[0][12], 0, 0);
		ft_change_cursor(game, x, y);
	}
	else
		mlx_mouse_show(game->mlx.ptr, game->mlx.win);
}

void	ft_display_select_menu(t_game *game)
{
	int	x;
	int	y;

	// mlx_mouse_show(game->mlx.ptr, game->mlx.win);
	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	ft_draw_img(&game->view, game->anim[0][4], 0, 0);
	ft_display_select_player(game, x, y);
	if (game->player == 1)
		ft_animation_v(game, &game->sprite[3], (t_vec2d) {1230, 370}, 0.08);
	else if (game->player == 2)
		ft_animation_v(game, &game->sprite[4], (t_vec2d) {1280, 530}, 0.08);
	else if (game->player == 3)
		ft_animation_v(game, &game->sprite[5], (t_vec2d) {1280, 470}, 0.08);
	ft_display_cat(game);
	if (game->ms >= 0.08)
		game->ms -= 0.08;
}

void    ft_display_players(t_game *game)
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
	{
		game->pause = 5;
		//mlx_mouse_show(game->mlx.ptr, game->mlx.win);
	}
}

void	ft_display_fly_menu(t_game *game)
{
	static int y = 0;
	static int x = 0;

	if (game->ms >= 0.001 && y >= -1800)
	{
		y -= 7;
		x += 10;
		game->ms -= 0.001;
		ft_draw_img(&game->view, game->anim[0][0], 0, 0);
		ft_draw_img(&game->view, game->anim[0][1], y, 0);
		ft_draw_img(&game->view, game->anim[0][2], x, 0);
		ft_draw_img(&game->view, game->anim[0][3], 0, y);
	}
	if (y < -1800)
		ft_display_players(game);
}

void	ft_select_settings(t_game *game)
{
	mlx_mouse_show(game->mlx.ptr, game->mlx.win);
	ft_draw_img(&game->view, game->anim[0][14], 0, 0);
	ft_draw_img(&game->view, game->anim[0][15], 0, 0);
	if (game->resolution == 1)
		ft_draw_img(&game->view, game->anim[0][16], 150, -30);
	else if (game->resolution == 2)
		ft_draw_img(&game->view, game->anim[0][17], 150, -30);
	else if (game->resolution == 4)
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
}

void	ft_display_settings_menu(t_game *game)
{
	static int x = WIDTH;

	ft_draw_img(&game->view, game->anim[0][4], 0, 0);
	if (x > 0)
	{
		if (game->player == 1)
			ft_animation_v(game, &game->sprite[3], (t_vec2d) {1230, 370}, 0.08);
		else if (game->player == 2)
			ft_animation_v(game, &game->sprite[4], (t_vec2d) {1280, 530}, 0.08);
		else if (game->player == 3)
			ft_animation_v(game, &game->sprite[5], (t_vec2d) {1280, 470}, 0.08);
		ft_display_cat(game);
	}
	if (game->ms >= 0.001 && x >= -WIDTH)
		x -= 15;
	if (x <= 0)
	{
		ft_draw_img(&game->view, game->anim[0][14], 0, 0);
		ft_draw_img(&game->view, game->anim[0][15], 0, 0);
	}
	ft_draw_img(&game->view, game->anim[0][13], x, 0);
	ft_select_settings(game);
}

void	ft_display_launch_game(t_game *game)
{
	static int x = WIDTH;

	ft_draw_img(&game->view, game->anim[0][4], 0, 0);
	if (x > 0)
	{
		if (game->player == 1)
			ft_animation_v(game, &game->sprite[3], (t_vec2d) {1230, 370}, 0.08);
		else if (game->player == 2)
			ft_animation_v(game, &game->sprite[4], (t_vec2d) {1280, 530}, 0.08);
		else if (game->player == 3)
			ft_animation_v(game, &game->sprite[5], (t_vec2d) {1280, 470}, 0.08);
		ft_display_cat(game);
	}
	if (game->ms >= 0.001 && x >= -WIDTH)
		x -= 15;
	if (x <= 0)
		game->pause = 0;
	ft_draw_img(&game->view, game->anim[0][13], x, 0);
}

void	ft_display_settings(t_game *game)
{
	(void)game;
	return ;
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

void	ft_transition(t_game *game)
{
	static int x = 0;

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
		ft_display_settings(game);
	if (game->pause == 0)
	{
		view_update_pos(game);
		view_update_dir_key(game);
		send_frame_job(game);
		wait_job(game);
		animation_fire(game);
		ft_transition(game);
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	if (game->pause != 3)
		game->ms += 0.0015;
	ft_printf_fps(0);
	return (0);
}
