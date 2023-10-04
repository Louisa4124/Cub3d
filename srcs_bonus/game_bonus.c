/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:53:49 by tlegrand          #+#    #+#             */
/*   Updated: 2023/10/04 13:27:49 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	ft_transition(t_game *game)
{
	static float	x = 0;

	if (game->ms >= 0.001 && x >= -WIDTH)
		x -= 40;
	ft_draw_img_vel(&game->view, game->anim[0][13], x, 0);
}

int	is_near(t_vec3d p1, t_vec3d p2, float e)
{
	t_vec3d	diff;

	diff = math_vec_op(p1, p2, '-');
	if (diff.x < -e || diff.x > e)
		return (0);
	if (diff.y < -e || diff.y > e)
		return (0);
	return (1);
}

void	run_game(t_game *game)
{
	view_update_pos(game);
	view_update_dir_key(game);
	update_igs_plane(game->igs, game->pos);
	update_doors_dist(game->doors, &game->pos, game->n_doors);
	update_door(game);
	if(send_frame_job(game))
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		ft_clean_exit(game, EXIT_FAILURE);
	}
	wait_job(game);
	display_map(&game->link, &game->minimap_size);
	animation_fire(game);
	ft_transition(game);
	ft_jump(game);
	if (is_near_door(game, game->doors, &game->pos) != -1)
		ft_animation_v(game, &game->sprite[18], (t_vec2d){670, 970}, 0.02);
	ft_printf_fps(FPS_MODE);
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
		run_game(game);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	update_igs_time(game->igs);
	if (game->pause != 6 && game->pause != 3)
		game->ms += 0.002;
	return (0);
}
