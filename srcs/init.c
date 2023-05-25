/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:26:19 by louisa            #+#    #+#             */
/*   Updated: 2023/05/25 15:36:25 by lboudjem         ###   ########.fr       */
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

void	s_texture_init(t_texture *texture)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		s_img_init(&texture->wall[i]);
		++i;
	}
	texture->floor = 0;
	texture->ceiling = 0;
}

void	ft_init_game(t_game *game)
{
	game->camera.x = 0;
	game->camera.y = 0;
	game->camera.z = 0.5;
	game->sky.a = 0;
	game->sky.b = 0;
	game->sky.c = 1;
	game->sky.d = -1;
	game->r_h = 2 * tan((FOV * PI / 180) * 0.5) / game->mlx.win_width;
	game->r_v = 2 * tan((FOV * PI / 180) * game->mlx.win_height / \
		(game->mlx.win_width * 2)) / game->mlx.win_height;
}
