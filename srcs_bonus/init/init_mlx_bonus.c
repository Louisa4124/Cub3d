/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:28:18 by louisa            #+#    #+#             */
/*   Updated: 2023/08/05 19:07:28 by tlegrand         ###   ########.fr       */
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
	game->view.addr = mlx_get_data_addr(game->view.id, \
		&game->view.bpp, &game->view.ll, &game->view.endian);
	if (!game->view.addr)
		return (ft_mlx_error(4, &game->mlx));
	game->view.height = game->mlx.win_height;
	game->view.width = game->mlx.win_width;
	return (0);
}

/*
void	*mlx_new_fullscreen_window(t_xvar *xvar, int *size_x, int *size_y,
		char *title)
{
	t_win_list				*new_win;
	XSetWindowAttributes	xswa;

	if (!(new_win = malloc(sizeof(*new_win))))
		return ((void *)0);
	xswa = get_default_attributes(xvar);
	xswa.override_redirect = 1;
	mlx_get_screen_size(xvar, size_x, size_y);
	new_win->window = XCreateWindow(xvar->display, xvar->root, 0, 0, *size_x,
			*size_y, 0, CopyFromParent, InputOutput, xvar->visual,
			CWEventMask | CWBackPixel | CWBorderPixel | CWColormap | CWOverrideRedirect,
			&xswa);
	return (set_configs(xvar, new_win, *size_x, *size_y, title));
}
*/


