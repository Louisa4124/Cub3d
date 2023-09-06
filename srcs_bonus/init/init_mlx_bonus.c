/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:28:18 by louisa            #+#    #+#             */
/*   Updated: 2023/09/06 13:03:02 by tlegrand         ###   ########.fr       */
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

int	new_image(t_mlx *mlx, t_img *new_img, int width, int height)
{
	new_img->width = width;
	new_img->height = height;
	new_img->id = mlx_new_image(mlx->ptr, new_img->width, new_img->height);
	if (new_img->id == NULL)
		return (ft_putstr_fd("Error\nCan't create new image\n", 2), 1);
	new_img->addr = mlx_get_data_addr(new_img->id, &new_img->bpp, \
		&new_img->ll, &new_img->endian);
	if (new_img->addr == NULL)
		return (ft_putstr_fd("Error\nCan't get new_image data\n", 2), 1);
	return (0);
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
	new_image(&game->mlx, &game->view, game->mlx.win_width, \
		game->mlx.win_height);
	return (0);
}

void	set_mlx_hook(t_game *game)
{
	mlx_loop_hook(game->mlx.ptr, update_game, game);
	mlx_hook(game->mlx.win, 2, 1L << 0, event_press, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, event_unpress, game);
	mlx_hook(game->mlx.win, 4, 1L << 2, event_pause, game);
	mlx_hook(game->mlx.win, 6, 1L << 6, event_mouse, game);
	mlx_hook(game->mlx.win, 8, 1L << 5, event_mouse_reset, game);
	mlx_hook(game->mlx.win, 17, 0L, close_event, game);
}

void	s_mlx_destroy(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
	mlx->win = NULL;
	mlx->ptr = NULL;
}
