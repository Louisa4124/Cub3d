/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:26:27 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/31 15:55:51 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_init_img(t_game *game)
{
	load_menu(game, 0, "img/start/1.xpm");
	load_menu(game, 13, "img/start/title.xpm");
	ft_draw_img(game, game->anim[0][0], 0, 0);
	ft_draw_img(game, game->anim[0][13], 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	load_menu(game, 1, "img/start/2.xpm");
	load_menu(game, 2, "img/start/3.xpm");
	load_menu(game, 3, "img/start/4.xpm");
	load_menu(game, 4, "img/start/5.xpm");
	load_menu(game, 5, "img/start/6.xpm");
	load_menu(game, 6, "img/start/7.xpm");
	load_menu(game, 7, "img/start/8.xpm");
	load_menu(game, 8, "img/start/9.xpm");
	load_menu(game, 9, "img/start/10.xpm");
	load_menu(game, 10, "img/start/11.xpm");
	load_menu(game, 11, "img/start/12.xpm");
	load_menu(game, 12, "img/start/13.xpm");
	load_img(game, 0, "img/anim/1.xpm");
	load_img(game, 1, "img/anim/2.xpm");
	load_img(game, 2, "img/anim/3.xpm");
	load_img(game, 3, "img/anim/4.xpm");
	load_img(game, 4, "img/anim/5.xpm");
	load_img(game, 5, "img/anim/6.xpm");
	load_img(game, 6, "img/anim/7.xpm");
	load_img(game, 7, "img/anim/8.xpm");
	load_img(game, 8, "img/anim/9.xpm");
	load_img(game, 9, "img/anim/10.xpm");
	load_img(game, 10, "img/anim/11.xpm");
	load_img(game, 11, "img/anim/12.xpm");
	load_img(game, 12, "img/anim/13.xpm");
	load_img(game, 13, "img/anim/14.xpm");
	load_img(game, 14, "img/anim/15.xpm");
	load_img(game, 15, "img/select/1.xpm");
	load_img(game, 16, "img/select/2.xpm");
	load_img(game, 17, "img/select/3.xpm");
	load_img(game, 18, "img/select/4.xpm");
	load_img(game, 19, "img/settings/1.xpm");
	load_img(game, 20, "img/settings/2.xpm");
	load_img(game, 21, "img/settings/3.xpm");
	load_img(game, 22, "img/settings/4.xpm");
	load_img(game, 23, "img/cat/0.xpm");
	load_img(game, 24, "img/cat/1.xpm");
	load_img(game, 25, "img/cat/3.xpm");
	load_img(game, 26, "img/cat/2.xpm");
	load_img(game, 27, "img/select/1.2.xpm");
	load_img(game, 28, "img/select/2.2.xpm");
	load_img(game, 29, "img/select/3.2.xpm");
	load_img(game, 30, "img/select/4.2.xpm");
}
