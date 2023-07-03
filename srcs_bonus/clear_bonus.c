/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:34:52 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/03 21:24:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	s_mlx_destroy(t_game *game)
{
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.ptr, game->mlx.win);
	if (game->mlx.ptr)
	{
		mlx_destroy_display(game->mlx.ptr);
		free(game->mlx.ptr);
	}
}

void	s_img_destroy(t_mlx *mlx, t_img *img)
{
	if (img->id)
		mlx_destroy_image(mlx->ptr, img->id);
	img->id = NULL;
	img->addr = NULL;
}

void	ft_destroy_texture(t_mlx *mlx, t_texture *texture)
{
	s_img_destroy(mlx, &texture->wall[0]);
	s_img_destroy(mlx, &texture->wall[1]);
	s_img_destroy(mlx, &texture->wall[2]);
	s_img_destroy(mlx, &texture->wall[3]);
}

void	ft_clean_exit(t_game *game, int exit_code)
{
	ft_destroy_texture(&game->mlx, &game->texture);
	s_mlx_destroy(game);
	ft_free2d((void **) game->map.layout, game->map.y_size);
	ft_free_secure(game->plan[0]);
	ft_free_secure(game->plan[1]);
	ft_free2d((void **) game->rays, game->mlx.win_height);
	exit(exit_code);
}
