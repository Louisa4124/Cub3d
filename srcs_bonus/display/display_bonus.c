/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/10/03 14:50:48 by tlegrand         ###   ########.fr       */
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
	idx_map.y = ((int)ln->pos->y) - MINIMAP_SIZE;
	idx_draw.y = 12;
	while (++idx_map.y < ((int)ln->pos->y) + MINIMAP_SIZE)
	{
		idx_map.x = ((int)ln->pos->x) - MINIMAP_SIZE;
		idx_draw.x = 12;
		while (++idx_map.x < ((int)ln->pos->x) + MINIMAP_SIZE)
		{
			draw_map(ln, &idx_map, &idx_draw, area);
			idx_draw.x += *(int *) area;
		}
		idx_draw.y += *(int *) area;
	}
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
	ft_memcpy(game->view.addr, game->view_data_cpy, \
		game->view.height * game->view.ll);
	ft_draw_img(&game->view, game->anim[0][15], 0, 0);
	if (game->resolution == 5)
		ft_draw_img(&game->view, game->anim[0][16], 150, -30);
	else if (game->resolution == 3)
		ft_draw_img(&game->view, game->anim[0][17], 150, -30);
	else if (game->resolution == 2)
		ft_draw_img(&game->view, game->anim[0][18], 150, -30);
	if (game->angle_offset >= 0.000 && game->angle_offset < 0.002)
		ft_draw_img(&game->view, game->anim[0][16], 150, 100);
	else if (game->angle_offset >= 0.002 && game->angle_offset < 0.004)
		ft_draw_img(&game->view, game->anim[0][17], 150, 100);
	else if (game->angle_offset >= 0.004)
		ft_draw_img(&game->view, game->anim[0][18], 150, 100);
	if (*game->link.light >= 0.2 && *game->link.light < 0.4)
		ft_draw_img(&game->view, game->anim[0][16], 150, 230);
	else if (*game->link.light >= 0.6 && *game->link.light < 0.8)
		ft_draw_img(&game->view, game->anim[0][17], 150, 230);
	else if (*game->link.light >= 1)
		ft_draw_img(&game->view, game->anim[0][18], 150, 230);
	ft_settings_mouse(game);
}
