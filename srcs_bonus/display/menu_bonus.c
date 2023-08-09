/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:43:27 by louisa            #+#    #+#             */
/*   Updated: 2023/08/09 14:05:46 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

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

void	ft_display_select_menu(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	ft_draw_img(&game->view, game->anim[0][4], 0, 0);
	ft_display_select_player(game, x, y);
	if (game->player == 1)
		ft_animation_v(game, &game->sprite[3], (t_vec2d) {1230, 370}, 0.08);
	else if (game->player == 2)
		ft_animation_v(game, &game->sprite[4], (t_vec2d) {1280, 530}, 0.08);
	else if (game->player == 3)
		ft_animation_v(game, &game->sprite[5], (t_vec2d) {1280, 470}, 0.08);
	ft_animation_cat(game);
	if (game->ms >= 0.08)
		game->ms -= 0.08;
}

void	ft_display_select_player(t_game *game, int x, int y)
{
	if ((x > 1500 && x < 1530) && (y > 640 && y < 675))
		ft_draw_img(&game->view, game->anim[0][9], 0, 0);
	else if ((x > 1235 && x < 1260) && (y > 640 && y < 675))
		ft_draw_img(&game->view, game->anim[0][8], 0, 0);
	else if ((x > 300 && x < 490) && (y > 550 && y < 590))
		ft_draw_img(&game->view, game->anim[0][10], 0, 0);
	else if ((x > 330 && x < 470) && (y > 650 && y < 680))
		ft_draw_img(&game->view, game->anim[0][11], 0, 0);
	else if ((x > 360 && x < 430) && (y > 745 && y < 780))
		ft_draw_img(&game->view, game->anim[0][12], 0, 0);
	if ((x > 1500 && x < 1530) && (y > 640 && y < 675))
		ft_change_cursor(game, x, y);
	else if ((x > 1235 && x < 1260) && (y > 640 && y < 675))
		ft_change_cursor(game, x, y);
	else if ((x > 300 && x < 490) && (y > 550 && y < 590))
		ft_change_cursor(game, x, y);
	else if ((x > 330 && x < 470) && (y > 650 && y < 680))
		ft_change_cursor(game, x, y);
	else if ((x > 360 && x < 430) && (y > 745 && y < 780))
		ft_change_cursor(game, x, y);
	else
		mlx_mouse_show(game->mlx.ptr, game->mlx.win);
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

void	ft_display_launch_game(t_game *game)
{
	static int	x = WIDTH;

	ft_draw_img(&game->view, game->anim[0][4], 0, 0);
	if (x > 0)
	{
		if (game->player == 1)
			ft_animation_v(game, &game->sprite[3], (t_vec2d) {1230, 370}, 0.08);
		else if (game->player == 2)
			ft_animation_v(game, &game->sprite[4], (t_vec2d) {1280, 530}, 0.08);
		else if (game->player == 3)
			ft_animation_v(game, &game->sprite[5], (t_vec2d) {1280, 470}, 0.08);
		ft_animation_cat(game);
	}
	if (game->ms >= 0.001 && x >= -WIDTH)
		x -= 15;
	if (x <= 0)
	{
		init_igs(game, game->igs);
		game->pause = 0;
	}
	ft_draw_img(&game->view, game->anim[0][13], x, 0);
}
