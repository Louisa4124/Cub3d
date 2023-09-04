/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:26:27 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/04 19:04:33 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	init_img(t_game *game)
{
	load_menu(game, 0, 0, "img/menu/background.xpm");
	load_menu(game, 0, 1, "img/menu/cloud1.xpm");
	load_menu(game, 0, 2, "img/menu/cloud2.xpm");
	load_menu(game, 0, 3, "img/menu/title.xpm");
	ft_draw_img(&game->view, game->anim[0][0], 0, 0);
	ft_draw_img(&game->view, game->anim[0][1], 0, 0);
	ft_draw_img(&game->view, game->anim[0][2], 0, 0);
	ft_draw_img(&game->view, game->anim[0][3], 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	load_menu(game, 0, 4, "img/select/all.xpm");
	load_menu(game, 0, 5, "img/select/clouds.xpm");
	load_menu(game, 0, 6, "img/select/sky.xpm");
	load_menu(game, 0, 7, "img/select/select.xpm");
	load_menu(game, 0, 8, "img/select/left.xpm");
	load_menu(game, 0, 9, "img/select/right.xpm");
	load_menu(game, 0, 10, "img/select/start.xpm");
	load_menu(game, 0, 11, "img/select/settings.xpm");
	load_menu(game, 0, 12, "img/select/exit.xpm");
	load_menu(game, 0, 13, "img/select/transition.xpm");
	
	load_menu(game, 0, 14, "img/settings/background.xpm");
	load_menu(game, 0, 15, "img/settings/all.xpm");
	load_menu(game, 0, 16, "img/settings/high.xpm");
	load_menu(game, 0, 17, "img/settings/medium.xpm");
	load_menu(game, 0, 18, "img/settings/low.xpm");

	load_menu(game, 1, 0, "img/select/0.xpm");
	load_menu(game, 1, 1, "img/cursor.xpm");

	load_menu(game, 1, 2, "img/torch.xpm");
	resize_image(game, &game->anim[1][2], 5);
	load_img(&game->mlx, &game->texture.t_floor, "img/grass2.xpm");
	load_img(&game->mlx, &game->texture.t_ceiling, "img/sky.xpm");
	load_img(&game->mlx, &game->texture.t_door, "img/door.xpm");

	return (0);
}

void	fill_all_sprite(t_game *game)
{
	fill_sprite(game, &game->sprite[0], 8);
	fill_sprite(game, &game->sprite[1], 10);
	fill_sprite(game, &game->sprite[2], 5);
	fill_sprite(game, &game->sprite[3], 6);
	fill_sprite(game, &game->sprite[4], 6);
	fill_sprite(game, &game->sprite[5], 6);
	fill_sprite(game, &game->sprite[6], 6);
	fill_sprite(game, &game->sprite[7], 8);
	fill_sprite(game, &game->sprite[8], 8);
	fill_sprite(game, &game->sprite[9], 8);
	fill_sprite(game, &game->sprite[10], 19);
	fill_sprite(game, &game->sprite[11], 10);
	fill_sprite(game, &game->sprite[12], 8);
	fill_sprite(game, &game->sprite[13], 5);
	fill_sprite(game, &game->sprite[14], 13);
	fill_sprite(game, &game->sprite[15], 8);
	fill_sprite(game, &game->sprite[16], 1);
	fill_sprite(game, &game->sprite[18], 19);
}

int	resize_all_sprite(t_game *game)
{
	int	err;

	err = 0;
	resize_image(game, &game->sprite[0].img, 7);
	resize_image(game, &game->sprite[1].img, 7);
	resize_image(game, &game->sprite[2].img, 7);
	resize_image(game, &game->sprite[3].img, 7);
	resize_image(game, &game->sprite[4].img, 7);
	resize_image(game, &game->sprite[5].img, 7);
	resize_image(game, &game->sprite[6].img, 4);
	resize_image(game, &game->sprite[7].img, 8);
	resize_image(game, &game->sprite[8].img, 8);
	resize_image(game, &game->sprite[9].img, 8);
	resize_image(game, &game->sprite[11].img, 3);
	resize_image(game, &game->sprite[12].img, 3);
	resize_image(game, &game->sprite[13].img, 3);
	resize_image(game, &game->sprite[14].img, 3);
	resize_image(game, &game->sprite[15].img, 3);
	resize_image(game, &game->sprite[16].img, 3);
	

	// game->sprite[0].img = resize_image(game, &game->sprite[0].img, 7);
	// game->sprite[1].img = resize_image(game, &game->sprite[1].img, 7);
	// game->sprite[2].img = resize_image(game, &game->sprite[2].img, 7);
	// game->sprite[3].img = resize_image(game, &game->sprite[3].img, 7);
	// game->sprite[4].img = resize_image(game, &game->sprite[4].img, 7);
	// game->sprite[5].img = resize_image(game, &game->sprite[5].img, 7);
	// game->sprite[6].img = resize_image(game, &game->sprite[6].img, 4);
	// game->sprite[7].img = resize_image(game, &game->sprite[7].img, 8);
	// game->sprite[8].img = resize_image(game, &game->sprite[8].img, 8);
	// game->sprite[9].img = resize_image(game, &game->sprite[9].img, 8);
	// game->sprite[11].img = resize_image(game, &game->sprite[11].img, 3);
	// game->sprite[12].img = resize_image(game, &game->sprite[12].img, 3);
	// game->sprite[13].img = resize_image(game, &game->sprite[13].img, 3);
	// game->sprite[14].img = resize_image(game, &game->sprite[14].img, 3);
	// game->sprite[15].img = resize_image(game, &game->sprite[15].img, 3);
	// game->sprite[16].img = resize_image(game, &game->sprite[16].img, 3);
	return (err);
}

int	load_all_sprite(t_game *game)
{
	int	err;

	err = load_img(&game->mlx, &game->sprite[0].img, "img/char1/all.xpm");
	err += load_img(&game->mlx, &game->sprite[1].img, "img/char3/all.xpm");
	err += load_img(&game->mlx, &game->sprite[2].img, "img/char2/all.xpm");
	err += load_img(&game->mlx, &game->sprite[3].img, "img/char1/idle.xpm");
	err += load_img(&game->mlx, &game->sprite[4].img, "img/char2/idle.xpm");
	err += load_img(&game->mlx, &game->sprite[5].img, "img/char3/idle.xpm");
	err += load_img(&game->mlx, &game->sprite[6].img, "img/load/1.xpm");
	err += load_img(&game->mlx, &game->sprite[7].img, "img/char2/fire.xpm");
	err += load_img(&game->mlx, &game->sprite[8].img, "img/char1/fire.xpm");
	err += load_img(&game->mlx, &game->sprite[9].img, "img/char3/fire.xpm");
	err += load_img(&game->mlx, &game->sprite[10].img, "img/menu/text.xpm");
	err += load_img(&game->mlx, &game->sprite[11].img, "img/cat/idle.xpm");
	err += load_img(&game->mlx, &game->sprite[12].img, "img/cat/laying.xpm");
	err += load_img(&game->mlx, &game->sprite[13].img, "img/cat/licking.xpm");
	err += load_img(&game->mlx, &game->sprite[14].img, "img/cat/stretch.xpm");
	err += load_img(&game->mlx, &game->sprite[15].img, "img/cat/walk.xpm");
	err += load_img(&game->mlx, &game->sprite[16].img, "img/cat/sleep.xpm");
	err += load_img(&game->mlx, &game->sprite[17].img, "img/fence.xpm");
	err += load_img(&game->mlx, &game->sprite[18].img, "img/text.xpm");

	return (err);
}

int	init_sprite(t_game *game)
{
	if (load_all_sprite(game))
		return (EXIT_FAILURE);
	if (resize_all_sprite(game))
		return (EXIT_FAILURE);
	fill_all_sprite(game);
	return (EXIT_SUCCESS);
}
