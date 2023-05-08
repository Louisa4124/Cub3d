/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:26:19 by louisa            #+#    #+#             */
/*   Updated: 2023/05/08 11:45:52 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

void	ft_init_game(t_game *game)
{
	game->camera.x = 0;
	game->camera.y = 0;
	game->camera.z = 0.5;
	game->r_h = 2 * tan((FOV * PI / 180) * 0.5) / W;
	game->r_v = 2 * tan((FOV * PI / 180) * H / (W * 2)) / H;
	ft_malloc_rays(game);
}

void	ft_init_rays(t_game *game)
{
	int				i;
	int				j;

	j = -1;
	while (++j < H)
	{
		i = -1;
		while (++i < W)
		{
			game->rays[i][j].x = ((j - W * 0.5) * game->r_h);
			game->rays[i][j].y = -1.0;
			game->rays[i][j].z = ((H * 0.5 - i) * game->r_v);
		}
	}
}
