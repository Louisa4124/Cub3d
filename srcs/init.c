/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:26:19 by louisa            #+#    #+#             */
/*   Updated: 2023/05/16 14:07:44 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	s_mlx_init(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
}

void	s_map_init(t_map *map)
{
	map->layout = NULL;
	map->x_size = 0;
	map->y_size = 0;
}

void	s_img_init(t_img *img)
{
	img->id = NULL;
	img->addr = NULL;
	img->height = 0;
	img->width = 0;
	img->ll = 0;
	img->bpp = 0;
	img->endian = 0;
}

void	ft_init_game(t_game *game)
{
	game->camera.x = 0;
	game->camera.y = 0;
	game->camera.z = 0.5;
	game->r_h = 2 * tan(FOV / 2) / WIDTH;
	game->r_v = 2 * tan(FOV * HEIGHT / (WIDTH * 2)) / HEIGHT;
	// game->r_h = 2 * tan((FOV * PI / 180) * 0.5) / W;
	// game->r_v = 2 * tan((FOV * PI / 180) * H / (W * 2)) / H;
}
