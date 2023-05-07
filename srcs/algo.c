/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/05/07 23:16:05 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_init_rays(void)
{
	int				i;
	int				j;

	j = -1;
	while (++j < H)
	{
		i = -1;
		while (++i < W)
		{
			game->rayon[i][j].x = ((j - game->twidth * 0.5) * r_h);
			game->rayon[i][j].y = -1.0;
			game->rayon[i][j].z = ((game->theight * 0.5 - i) * r_v);
		}
	}
}
