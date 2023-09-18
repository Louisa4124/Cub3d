/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:40:03 by louisa            #+#    #+#             */
/*   Updated: 2023/09/18 21:23:53 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_settings_mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	if ((x > 1170 && x < 1200) && (y > 500 && y < 520))
		ft_change_cursor(game, x, y);
	else if ((x > 1015 && x < 1045) && (y > 500 && y < 520))
		ft_change_cursor(game, x, y);
	else if ((x > 1170 && x < 1200) && (y > 620 && y < 650))
		ft_change_cursor(game, x, y);
	else if ((x > 1015 && x < 1045) && (y > 620 && y < 650))
		ft_change_cursor(game, x, y);
	else if ((x > 1015 && x < 1045) && (y > 760 && y < 780))
		ft_change_cursor(game, x, y);
	else if ((x > 1170 && x < 1200) && (y > 760 && y < 780))
		ft_change_cursor(game, x, y);
	else if (((x > 50 && x < 280) && (y > 1000 && y < 1050)))
		ft_change_cursor(game, x, y);
	else
		better_mlx_mouse_show(game->mlx.ptr, game->mlx.win, &game->cursor);
}

void	ft_select_settings(t_game *game)
{
	ft_draw_img(&game->view, game->anim[0][14], 0, 0);
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

static int	set_pause_settings(t_game *game)
{
	game->pause = 1;
	return (WIDTH);
}

void	ft_display_settings_menu(t_game *game)
{
	static int	x = WIDTH;

	ft_draw_img(&game->view, game->anim[0][4], 0, 0);
	if (x > 0)
	{
		if (game->player == 1)
			ft_animation_v(game, &game->sprite[3], (t_vec2d){1230, 370}, 0.08);
		else if (game->player == 2)
			ft_animation_v(game, &game->sprite[4], (t_vec2d){1280, 530}, 0.08);
		else if (game->player == 3)
			ft_animation_v(game, &game->sprite[5], (t_vec2d){1280, 470}, 0.08);
		ft_animation_cat(game, 0.05);
	}
	if (game->ms >= 0.001 && x >= -WIDTH)
		x -= 15;
	if (x <= 0)
	{
		ft_draw_img(&game->view, game->anim[0][14], 0, 0);
		ft_draw_img(&game->view, game->anim[0][15], 0, 0);
	}
	ft_draw_img(&game->view, game->anim[0][13], x, 0);
	better_mlx_mouse_show(game->mlx.ptr, game->mlx.win, &game->cursor);
	if (x <= -WIDTH)
		x = set_pause_settings(game);
}
