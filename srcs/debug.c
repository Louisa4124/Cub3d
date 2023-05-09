/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:33:34 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/08 21:55:37 by tlegrand         ###   ########.fr       */
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

void	debug_printf_texture(t_texture *texture)
{
	dprintf(2, "####	t_texture	####\n");
	debug_print_img(&texture->north);
	debug_print_img(&texture->south);
	debug_print_img(&texture->east);
	debug_print_img(&texture->west);
	dprintf(2, "t->color floor : %#X\n", texture->floor);
	dprintf(2, "t->color ceiling : %#X\n", texture->ceiling);
	dprintf(2, "	----	\n");
}
