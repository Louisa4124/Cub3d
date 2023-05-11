/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:26:19 by louisa            #+#    #+#             */
/*   Updated: 2023/05/11 17:44:00 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_plan	*ft_malloc_plan_v(void)
{
	t_plan		*plan;

	plan = malloc(sizeof(t_plan) * (WIDTH + 2));
	return (plan);
}

t_plan	*ft_malloc_plan_h(void)
{
	t_plan		*plan;

	plan = malloc(sizeof(t_plan) * (HEIGHT + 2));
	return (plan);
}

t_vec3d	**ft_malloc_rays(void)
{
	t_vec3d		**rays;
	int			x;

	x = 0;
	rays = ft_calloc(sizeof(t_vec3d *), (H + 1));
	while (x < H)
	{
		rays[x] = ft_calloc(sizeof(t_vec3d), (W + 1));
		x++;
	}
	return (rays);
}

void	s_mlx_init(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
}

void	s_map_init(t_map *map)
{
	map->layout = NULL;
	map->x_size = 0;
	map->y_size = 0;
}

void	s_img_init(t_img *img)
{
	img->id = NULL;
	img->addr = NULL;
	img->height = 0;
	img->width = 0;
	img->ll = 0;
	img->bpp = 0;
	img->endian = 0;
}

void	ft_init_game(t_game *game)
{
	game->pos.x = 1;
	game->pos.y = 0;
	game->pos.z = 1;

	game->angle_z = 0;
	game->angle_x = 0;

	game->camera.x = 0;
	game->camera.y = 0;
	game->camera.z = 0.5;

	game->plan[0] = ft_malloc_plan_h();
	game->plan[1] = ft_malloc_plan_v();

	// game->plan[0][0].a = 0;
	// game->plan[0][0].b = 1;
	// game->plan[0][0].c = 0;
	// game->plan[0][0].d = 4;

	// game->plan[0][1].a = 0;
	// game->plan[0][1].b = 1;
	// game->plan[0][1].c = 0;
	// game->plan[0][1].d = -4;

	// game->plan[1][0].a = 1;
	// game->plan[1][0].b = 0;
	// game->plan[1][0].c = 0;
	// game->plan[1][0].d = 4;

	// game->plan[1][1].a = 1;
	// game->plan[1][1].b = 0;
	// game->plan[1][1].c = 0;
	// game->plan[1][1].d = -4;

	game->dir.x = 1;
	game->dir.y = 0;
	game->dir.z = 0;
	game->r_h = 2 * tan(FOV / 2) / W;
	game->r_v = 2 * tan(FOV * H / (W * 2)) / H;
	// game->r_h = 2 * tan((FOV * PI / 180) * 0.5) / W;
	// game->r_v = 2 * tan((FOV * PI / 180) * H / (W * 2)) / H;
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
			game->rays[j][i].x = ((j - W * 0.5) * game->r_h);
			game->rays[j][i].y = -1.0;
			game->rays[j][i].z = ((H * 0.5 - i) * game->r_v);
		}
	}
}
