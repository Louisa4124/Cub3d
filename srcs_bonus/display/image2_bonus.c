/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:39:31 by louisa            #+#    #+#             */
/*   Updated: 2023/08/05 18:56:08 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

// draw_on(NULL, (t_vec2d) {1,2}, NULL, (t_area) {1, 0, 40, 12});

void	draw_on(t_img *img_dst, t_vec2d pos, t_img img_src, t_area area)
{
	char	*dst;
	char	*src;
	int		i;
	int		j;

	pos.x -= area.start_x;
	pos.y -= area.start_y;
	i = area.start_y - 1;
	while (++i < area.end_y && i < img_src.height)
	{
		j = area.start_x - 1;
		while (++j < area.end_x && j < img_src.width)
		{
			if ((pos.x + j) < WIDTH && (pos.x + j) >= 0 
				&& (pos.y + i) < HEIGHT && (pos.y + i) >= 0)
			{
				dst = (img_dst->addr + ((pos.y + i) * img_dst->ll + (pos.x + j) \
					*(img_dst->bpp >> 3)));
				src = (img_src.addr + (i * img_src.ll + j *(img_src.bpp >> 3)));
				if (*(unsigned int *)src != 0xff000000)
					*(unsigned int *)dst = *(unsigned int *)src;
			}
		}
	}
}

void	ft_draw_img(t_img *img_dst, t_img tex, int x, int y)
{
	char	*dst;
	char	*src;
	int		i;
	int		j;

	i = 0;
	while (i < tex.height)
	{
		j = 0;
		while (j < tex.width)
		{
			if ((x + j) < WIDTH && (x + j) >= 0 && (y + i) < HEIGHT 
				&& (y + i) >= 0)
			{
				dst = (img_dst->addr + ((y + i) * img_dst->ll + (x + j)
							*(img_dst->bpp >> 3)));
				src = (tex.addr + (i * tex.ll + j
							*(tex.bpp >> 3)));
				if (*(unsigned int *)src != 0xff000000)
					*(unsigned int *)dst = *(unsigned int *)src;
			}
			++j;
		}
		++i;
	}
}

t_img	resize_image(t_game *game, t_img *src, int ratio)
{
	t_img	new_img;
	t_vec2d	src_pos;
	t_vec2d	index;
	t_vec2d	pix_index;
	int		byte;

	index.y = 0;
	new_img.width = src->width * ratio;
	new_img.height = src->height * ratio;
	new_img.id = mlx_new_image(game->mlx.ptr, new_img.width, new_img.height);
	new_img.addr = mlx_get_data_addr(new_img.id, &new_img.bpp, &new_img.ll, &new_img.endian);
	while (index.y < new_img.height)
	{
		index.x = 0;
		while (index.x < new_img.width)
		{
			src_pos.x = index.x * src->width / new_img.width;
			src_pos.y = index.y * src->height / new_img.height;
			pix_index.x = (src_pos.y * src->ll) + (src_pos.x * (src->bpp >> 3));
			pix_index.y = (index.y * new_img.ll) + (index.x * (new_img.bpp >> 3));
			byte = 0;
			while (byte < (new_img.bpp >> 3))
			{
				new_img.addr[pix_index.y + byte] = src->addr[pix_index.x + byte];
				++byte;
			}
			++index.x;
		}
		++index.y;
	}
	mlx_destroy_image(game->mlx.ptr, src->id);
	return (new_img);
}
