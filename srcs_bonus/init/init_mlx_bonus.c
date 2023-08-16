/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:28:18 by louisa            #+#    #+#             */
/*   Updated: 2023/08/16 13:09:09 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	ft_mlx_error(int errnum, t_mlx *mlx)
{
	if (errnum == 0)
		return (EXIT_SUCCESS);
	s_mlx_destroy(mlx);
	if (errnum == 1)
		ft_putstr_fd("Error\nMlx init fail\n", 2);
	else if (errnum == 2)
		ft_putstr_fd("Error\nNew window fail\n", 2);
	else if (errnum == 3)
		ft_putstr_fd("Error\nNew image fail\n", 2);
	else if (errnum == 4)
		ft_putstr_fd("Error\nGet data from image fail\n", 2);
	return (EXIT_FAILURE);
}

int	ft_init_mlx(t_game *game)
{
	game->mlx.ptr = mlx_init();
	if (!game->mlx.ptr)
		return (ft_mlx_error(1, NULL));
	game->mlx.win_width = WIDTH;
	game->mlx.win_height = HEIGHT;
	game->mlx.win = mlx_new_window(game->mlx.ptr, \
		game->mlx.win_width, game->mlx.win_height, "cub3D");
	if (!game->mlx.win)
		return (ft_mlx_error(2, &game->mlx));
	game->view.id = mlx_new_image(game->mlx.ptr, \
		game->mlx.win_width, game->mlx.win_height);
	if (!game->view.id)
		return (ft_mlx_error(3, &game->mlx));
	game->blur.id = mlx_new_image(game->mlx.ptr, \
		game->mlx.win_width, game->mlx.win_height);
	if (!game->blur.id)
		return (ft_mlx_error(3, &game->mlx));
	game->blur.addr = mlx_get_data_addr(game->blur.id, \
		&game->blur.bpp, &game->blur.ll, &game->blur.endian);
	if (!game->blur.addr)
	{
		s_img_destroy(&game->mlx, &game->view);
		return (ft_mlx_error(4, &game->mlx));
	}
	game->view.addr = mlx_get_data_addr(game->view.id, \
		&game->view.bpp, &game->view.ll, &game->view.endian);
	if (!game->view.addr)
	{
		s_img_destroy(&game->mlx, &game->view);
		return (ft_mlx_error(4, &game->mlx));
	}
	game->view.height = game->mlx.win_height;
	game->view.width = game->mlx.win_width;
	return (0);
}
