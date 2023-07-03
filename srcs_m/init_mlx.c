/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:28:18 by louisa            #+#    #+#             */
/*   Updated: 2023/07/03 21:41:06 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_mlx_error(int errnum)
{
	if (errnum == NO_ERR)
		return (EXIT_SUCCESS);
	else if (errnum == MLX_ERR_INIT)
		ft_putstr_fd("Error\nMlx init fail\n", 2);
	else if (errnum == MLX_ERR_WINDOW)
		ft_putstr_fd("Error\nNew window fail\n", 2);
	else if (errnum == MLX_ERR_IMAGE)
		ft_putstr_fd("Error\nNew image fail\n", 2);
	else if (errnum == 4)
		ft_putstr_fd("Error\nGet data from image fail\n", 2);
	return (EXIT_FAILURE);
}

int	ft_init_mlx(t_game *game)
{
	s_mlx_init(&game->mlx);
	game->mlx.ptr = mlx_init();
	if (!game->mlx.ptr)
		return (MLX_ERR_INIT);
	game->mlx.win_width = WIDTH;
	game->mlx.win_height = HEIGHT;
	game->mlx.win = mlx_new_window(game->mlx.ptr, \
		game->mlx.win_width, game->mlx.win_height, "cub3D");
	if (!game->mlx.win)
		return (ft_destroy_mlx(game), MLX_ERR_WINDOW);
	game->view.id = mlx_new_image(game->mlx.ptr, game->mlx.win_width, game->mlx.win_height);
	if (!game->view.id)
		return (ft_destroy_mlx(game), MLX_ERR_IMAGE);
	game->view.addr = mlx_get_data_addr(game->view.id, &game->view.bpp, &game->view.ll, &game->view.endian);
	if (!game->view.addr)
		return (ft_destroy_mlx(game), MLX_ERR_DATA);
	game->view.height = game->mlx.win_height;
	game->view.width = game->mlx.win_width;
	return (NO_ERR);
}

void	ft_destroy_mlx(t_game *game)
{
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.ptr, game->mlx.win);
	if (game->mlx.ptr)
	{
		mlx_destroy_display(game->mlx.ptr);
		free(game->mlx.ptr);
	}
}
