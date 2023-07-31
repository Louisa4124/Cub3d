/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:39:31 by louisa            #+#    #+#             */
/*   Updated: 2023/07/31 16:34:27 by lboudjem         ###   ########.fr       */
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
