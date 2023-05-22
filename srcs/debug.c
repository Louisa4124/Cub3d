/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:33:34 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/22 11:17:36 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	debug_print_mlx(t_mlx *mlx)
{
	dprintf(2, "####	t_mlx	####\n");
	dprintf(2, "mlx->ptr : %p\n", mlx->ptr);
	dprintf(2, "mlx->win : %p\n", mlx->win);
	dprintf(2, "	----	\n");
}

void	debug_print_img(t_img *img)
{
	dprintf(2, "####	t_img	####\n");
	dprintf(2, "img->id : %p\n", img->id);
	dprintf(2, "img->addr : %p\n", img->addr);
	dprintf(2, "img->height: %d\n", img->height);
	dprintf(2, "img->width: %d\n", img->width);
	dprintf(2, "img->ll: %d\n", img->ll);
	dprintf(2, "img->bpp: %d\n", img->bpp);
	dprintf(2, "img->endian: %d\n", img->endian);
	dprintf(2, "	----	\n");
}

void	debug_print_texture(t_texture *texture)
{
	int	i;

	i = 0;
	dprintf(2, "####	t_texture	####\n");
	while (i < 4)
	{
		debug_print_img(&texture->wall[i]);
		++i;
	}
	dprintf(2, "t->color floor : %#X\n", texture->floor);
	dprintf(2, "t->color ceiling : %#X\n", texture->ceiling);
	dprintf(2, "	----	\n");
}

void	debug_print_map(t_map *map)
{
	int	i;
	int	j;

	dprintf(2, "####	t_map	####\n");
	dprintf(2, "map->y_size : %d\n", map->y_size);
	dprintf(2, "map->x_size : %d\n", map->x_size);
	i = -1;
	while (++i < map->y_size)
	{
		j = -1;
		while (++j < map->x_size)
			dprintf(2, "%3d", map->layout[i][j]);
		dprintf(2, "\n");
	}
	dprintf(2, "	----	\n");
}
