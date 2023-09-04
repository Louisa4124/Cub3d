/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_resize_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:32:18 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/05 00:28:37 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	copy_scale(t_vec2d *src_pos, t_vec2d *index, t_img *src, \
	t_img *new_img)
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
			copy_scale(&src_pos, &index, src, &new_img);
			++index.x;
		}
		++index.y;
	}
	mlx_destroy_image(game->mlx.ptr, src->id);
	*src = new_img;
	return (0);
}
