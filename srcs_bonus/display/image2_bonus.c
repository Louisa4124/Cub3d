/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:39:31 by louisa            #+#    #+#             */
/*   Updated: 2023/07/31 15:22:19 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void    ft_draw_img(t_game *game, t_img tex, int x, int y)
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
            if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
            {
                dst = (game->view.addr + ((y + i) * game->view.ll + (x + j)
                            *(game->view.bpp >> 3)));
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
