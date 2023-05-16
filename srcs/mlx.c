/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:28:18 by louisa            #+#    #+#             */
/*   Updated: 2023/05/16 14:08:03 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_init_mlx(t_game *game)
{
	game->mlx.ptr = mlx_init();
	if (!game->mlx.ptr)
	{
		ft_putstr_fd("Error\nMlx init fail\n", 2);
		return (1);
	}
	game->mlx.win = mlx_new_window(game->mlx.ptr, WIDTH, HEIGHT, "cub3D");
	if (!game->mlx.win)
	{
		mlx_destroy_display(game->mlx.ptr);
		free(game->mlx.ptr);
		ft_putstr_fd("Error\nNew window fail\n", 2);
		return (1);
	}
	return (0);
}

/*
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

void	ft_clean_exit(t_game *game, int exit_code)
{
	ft_destroy_mlx(game);
	exit(exit_code);
}

*/
int	close_event(t_game *game)
{
	mlx_destroy_window(game->mlx.ptr, game->mlx.win);
	//mlx_destroy_image(game->mlx.ptr, game->mlx.image);
	free(game->mlx.ptr);
	exit (0);
	return (0);
}
