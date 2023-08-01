/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:39:31 by louisa            #+#    #+#             */
/*   Updated: 2023/07/31 20:57:52 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void    ft_draw_img(t_img *img_dst, t_img tex, int x, int y)
{
    char    *dst;
    char    *src;
    int        i;
    int        j;

    i = 0;
    while (i < tex.height)
    {
        j = 0;
        while (j < tex.width)
        {
            if ((x + j) < WIDTH && (x + j) >= 0 && (y + i) < HEIGHT && (y + i) >= 0)
            {
                dst = (img_dst->addr + ((y + i) * img_dst->ll + (x + j)
                            *(img_dst->bpp >> 3)));
                src = (tex.addr + (i * tex.ll + j
                            *(tex.bpp >> 3)));
                if (*(unsigned *)src != 0xff000000)
                    *(unsigned long *)dst = *(unsigned long *)src;
            }
            j++;
        }
        i++;
    }
}

t_img resize_image(t_game *game, t_img *source, int new_width, int new_height)
{
    t_img new_img;

    new_img.id = mlx_new_image(game->mlx.ptr, new_width, new_height);
    new_img.addr = mlx_get_data_addr(new_img.id, &new_img.bpp, &new_img.ll, &new_img.endian);
    new_img.width = new_width;
    new_img.height = new_height;
    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int src_x = x * source->width / new_width;
            int src_y = y * source->height / new_height;
            int src_pixel_index = (src_y * source->ll) + (src_x * (source->bpp / 8));
            int dst_pixel_index = (y * new_img.ll) + (x * (new_img.bpp / 8));

            for (int byte = 0; byte < (new_img.bpp / 8); byte++)
                new_img.addr[dst_pixel_index + byte] = source->addr[src_pixel_index + byte];
        }
    }
    return new_img;
}
