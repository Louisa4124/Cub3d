/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:26:19 by louisa            #+#    #+#             */
/*   Updated: 2023/05/08 13:00:53 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
void	ft_init_game(t_game *game)
{
	game->camera.x = 0;
	game->camera.y = 0;
	game->camera.z = 0.5;
	game->r_h = 2 * tan(FOV / 2) / W;
	game->r_v = 2 * tan(FOV * H / (W * 2)) / H;
	// game->r_h = 2 * tan((FOV * PI / 180) * 0.5) / W;
	// game->r_v = 2 * tan((FOV * PI / 180) * H / (W * 2)) / H;
}

t_vec3d	**ft_malloc_rays(t_game *game)
{
	t_vec3d		**rays;
	int			x;

	x = 0;
	rays = malloc(sizeof(t_vec3d *) * H + 1);
	while (x < H)
	{
		rays[x] = malloc(sizeof(t_vec3d) * W + 1);
		x++;
	}
	return (rays);
}
*/