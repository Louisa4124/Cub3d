/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/04 21:46:19 by tlegrand         ###   ########.fr       */
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

	game->pause = 3;
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

}

void    ft_display_menu(t_game *game)
{
	static int	i = 0;

	if (game->ms >= 0.025)
	{
		i++;
		game->ms -= 0.025;
	}
	if (i >= 13)
		i = 0;
	ft_draw_img(&game->view, game->anim[0][i], 0, 0);
	ft_draw_img(&game->view, game->anim[0][13], 0, 0);
}

void    ft_display_select_player(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	ft_draw_img(&game->view, game->anim[0][14], 0, 0);
	ft_draw_img(&game->view, game->anim[1][0], 0, 0);
	if ((x > 550 && x < 650) && (y > 650 && y < 920))
	{
		ft_animation(game, &game->sprite[0], (t_vec2d) {0, 500});
		ft_animation(game, &game->sprite[4], (t_vec2d) {900, 645});
		ft_animation(game, &game->sprite[5], (t_vec2d) {1250, 590});
	}
	else if ((x > 1320 && x < 1410) && (y > 670 && y < 920))
	{
		ft_animation(game, &game->sprite[1], (t_vec2d) {1070, 550});
		ft_animation(game, &game->sprite[3], (t_vec2d) {450, 500});
		ft_animation(game, &game->sprite[4], (t_vec2d) {900, 645});	
	}
	else if ((x > 950 && x < 1050) && (y > 710 && y < 920))
	{
		ft_animation(game, &game->sprite[2], (t_vec2d) {850, 600});
		ft_animation(game, &game->sprite[3], (t_vec2d) {450, 500});
		ft_animation(game, &game->sprite[5], (t_vec2d) {1250, 590});
	}
	else
	{
		ft_animation(game, &game->sprite[3], (t_vec2d) {450, 500});
		ft_animation(game, &game->sprite[4], (t_vec2d) {900, 645});
		ft_animation(game, &game->sprite[5], (t_vec2d) {1250, 590});
	}
	if (game->ms >= 0.02)
		game->ms -= 0.02;
}

void    ft_display_fly_menu(t_game *game)
{
	static int y = 0;
	static int x = 14;

	if (game->ms >= 0.004 && y >= -800)
	{
		y -= 10;
		game->ms -= 0.004;
		ft_draw_img(&game->view, game->anim[0][14], 0, 0);
		ft_draw_img(&game->view, game->anim[0][13], 0, y);
	}
	if (game->ms >= 0.04 && y < -800 && x < 22)
	{
		x++;
		game->ms -= 0.04;
		ft_draw_img(&game->view, game->anim[0][x], 0, 0);
	}
	if (x == 21)
		game->pause = 5;
}

void    ft_display_load(t_game *game)
{
	static int	x = 22;
	static int	y = 0;

	if (game->ms >= 0.05 && x > 14)
	{
		x--;
		game->ms -= 0.05;
		ft_draw_img(&game->view, game->anim[0][x], 0, 0);
	}
	if (x <= 14 && x > 0)
	{
		ft_draw_img(&game->view, game->anim[0][14], 0, 0);
		y += ft_animation_h(game, &game->sprite[6], (t_vec2d){900, 600}, 0.05);
		if (game->ms >= 0.05)
			game->ms -= 0.05;
	}
	if (y == 2)
		game->pause = 0;
}

void	ft_display_settings(t_game *game)
{

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

int	update_game(t_game *game)
{
	t_vec2d	pos = (t_vec2d){1100, 300};

	if (game->pause == 6)
		ft_display_load(game);
	if (game->pause == 5)
		ft_display_select_player(game);
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
		send_job(game);
		// wait_job(game);
		if (add_job(game, &game->sprite[3], &pos, fredimation))
			return (1);
		wait_job(game);
		animation_fire(game);
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	if (game->pause != 3)
		game->ms += 0.0015;
	ft_printf_fps(0);
	return (0);
}



/*
void	*mlx_new_fullscreen_window(t_xvar *xvar, int *size_x, int *size_y,
		char *title)
{
	t_win_list				*new_win;
	XSetWindowAttributes	xswa;

	if (!(new_win = malloc(sizeof(*new_win))))
		return ((void *)0);
	xswa = get_default_attributes(xvar);
	xswa.override_redirect = 1;
	mlx_get_screen_size(xvar, size_x, size_y);
	new_win->window = XCreateWindow(xvar->display, xvar->root, 0, 0, *size_x,
			*size_y, 0, CopyFromParent, InputOutput, xvar->visual,
			CWEventMask | CWBackPixel | CWBorderPixel | CWColormap | CWOverrideRedirect,
			&xswa);
	return (set_configs(xvar, new_win, *size_x, *size_y, title));
}
*/

