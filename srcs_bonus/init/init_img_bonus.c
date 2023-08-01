/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:26:27 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/01 14:56:40 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_init_img(t_game *game)
{
	load_menu(game, 0,  0, "img/start/1.xpm");
	load_menu(game, 0, 13, "img/start/title.xpm");
	ft_draw_img(&game->view, game->anim[0][0], 0, 0);
	ft_draw_img(&game->view, game->anim[0][13], 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	load_menu(game, 0, 1, "img/start/2.xpm");
	load_menu(game, 0, 2, "img/start/3.xpm");
	load_menu(game, 0, 3, "img/start/4.xpm");
	load_menu(game, 0, 4, "img/start/5.xpm");
	load_menu(game, 0, 5, "img/start/6.xpm");
	load_menu(game, 0, 6, "img/start/7.xpm");
	load_menu(game, 0, 7, "img/start/8.xpm");
	load_menu(game, 0, 8, "img/start/9.xpm");
	load_menu(game, 0, 9, "img/start/10.xpm");
	load_menu(game, 0, 10, "img/start/11.xpm");
	load_menu(game, 0, 11, "img/start/12.xpm");
	load_menu(game, 0, 12, "img/start/13.xpm");
	load_menu(game, 0, 14, "img/start/background.xpm");
	load_menu(game, 0, 15, "img/start/14.xpm");
	load_menu(game, 0, 16, "img/start/15.xpm");
	load_menu(game, 0, 17, "img/start/16.xpm");
	load_menu(game, 0, 18, "img/start/17.xpm");
	load_menu(game, 0, 19, "img/start/18.xpm");
	load_menu(game, 0, 20, "img/start/19.xpm");
	load_menu(game, 0, 21, "img/start/20.xpm");
	load_menu(game, 0, 22, "img/start/21.xpm");

	load_menu(game, 1, 0, "img/select/0.xpm");
	load_menu(game, 1, 1, "img/select/1.xpm");
	load_menu(game, 1, 2, "img/select/2.xpm");
	load_menu(game, 1, 3, "img/select/3.xpm");
	
	load_menu(game, 2, 0, "img/char1/all.xpm");
	game->anim[2][0] = resize_image(game, &game->anim[2][0], 7);
	load_menu(game, 2, 1, "img/char1/idle.xpm");
	game->anim[2][1] = resize_image(game, &game->anim[2][1], 7);

	load_menu(game, 3, 0, "img/char3/all.xpm");
	game->anim[3][0] = resize_image(game, &game->anim[3][0], 7);
	
	load_menu(game, 4, 0, "img/char2/all.xpm");
	game->anim[4][0] = resize_image(game, &game->anim[4][0], 7);
}
