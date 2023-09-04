/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_resize_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:32:18 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/04 18:32:34 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

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

void	calculus(t_vec2d *src_pos, t_vec2d *index, t_img *src, t_img *new_img)
{
	t_vec2d	p_index;
	int		byte;

	byte = 0;
	src_pos->x = index->x * src->width / new_img->width;
	src_pos->y = index->y * src->height / new_img->height;
	p_index.x = (src_pos->y * src->ll) + (src_pos->x * (src->bpp >> 3));
	p_index.y = (index->y * new_img->ll) + (index->x * (new_img->bpp >> 3));
	while (byte < (new_img->bpp >> 3))
	{
		new_img->addr[p_index.y + byte] = src->addr[p_index.x + byte];
		++byte;
	}
}

int	resize_image(t_game *game, t_img *src, int r)
{
	t_img	new_img;
	t_vec2d	src_pos;
	t_vec2d	index;

	index.y = 0;
	if (new_image(&game->mlx, &new_img, src->width * r, src->height * r))
		return (1);
	while (index.y < new_img.height)
	{
		index.x = 0;
		while (index.x < new_img.width)
		{
			calculus(&src_pos, &index, src, &new_img);
			++index.x;
		}
		++index.y;
	}
	mlx_destroy_image(game->mlx.ptr, src->id);
	*src = new_img;
	return (0);
}
