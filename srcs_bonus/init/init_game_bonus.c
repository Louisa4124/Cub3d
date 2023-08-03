/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/03 22:42:36 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	plane_create(t_game *game)
{
	int	i;

	game->plan[0] = malloc(sizeof(t_plan) * (game->map.y_size + 1));
	game->plan[1] = malloc(sizeof(t_plan) * (game->map.x_size + 1));
	if (!game->plan[0] || !game->plan[1])
		return (EXIT_FAILURE);
	i = 0;
	while (i < game->map.y_size)
	{
		game->plan[0][i].a = 0;
		game->plan[0][i].b = 1;
		game->plan[0][i].c = 0;
		game->plan[0][i].d = -i;
		++i;
	}
	i = 0;
	while (i < game->map.x_size)
	{
		game->plan[1][i].a = 1;
		game->plan[1][i].b = 0;
		game->plan[1][i].c = 0;
		game->plan[1][i].d = -i;
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	rays_create(t_game *game)
{
	int		i;
	int		j;

	game->rays = malloc(sizeof(t_vec3d *) * game->mlx.win_height);
	if (!game->rays)
		return (EXIT_FAILURE);
	i = 0;
	while (i < game->mlx.win_height)
	{
		game->rays[i] = malloc(sizeof(t_vec3d) * game->mlx.win_width);
		if (!game->rays[i])
			return (EXIT_FAILURE);
		j = 0;
		while (j < game->mlx.win_width)
		{
			game->rays[i][j].x = ((j - game->mlx.win_width * 0.5) * 2 * \
				tan((FOV * PI_DIV_180) * 0.5) / game->mlx.win_width);
			game->rays[i][j].y = -1.0;
			game->rays[i][j].z = ((game->mlx.win_height * 0.5 - i) * \
				tan((FOV * PI_DIV_180) / game->mlx.win_width));
			++j;
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_init_game(t_game *game)
{
	game->bit_key = 0;
	game->pause = 0;
	game->angle_x = -0.1;
	game->plan[0] = NULL;
	game->plan[1] = NULL;
	game->rays = NULL;
	game->minimap_size = 10;
	if (rays_create(game))
		return (EXIT_FAILURE);
	if (plane_create(game))
		return (EXIT_FAILURE);
	if (sem_init(&game->sem_thread, 0, 0) == -1)
		dprintf(2, "Error sem_init\n");
	if (sem_init(&game->sem_main, 0, 0) == -1)
		dprintf(2, "Error sem_init\n");
	pthread_mutex_init(&game->m_queue, NULL);
	return (EXIT_SUCCESS);
}

void	init_area_link(t_game *game)
{
	int	i;

	i = 0;
	while (i < N_CHUNK)
	{
		game->area[i].start_y = i * (game->mlx.win_height / N_CHUNK);
		game->area[i].end_y = (i + 1) * (game->mlx.win_height / N_CHUNK);
		game->area[i].start_x = 0;
		game->area[i].end_x = game->mlx.win_width;
		++i;
	}
	game->area[--i].end_y = game->mlx.win_height;
	game->link.map = &game->map;
	game->link.pos = &game->pos;
	game->link.rays = game->rays;
	game->link.plan[0] = game->plan[0];
	game->link.plan[1] = game->plan[1];
	game->link.angle_x = &game->angle_x;
	game->link.angle_z = &game->angle_z;
	game->link.view = &game->view;
	game->link.texture = &game->texture;
	game->link.mm_size = &game->minimap_size;
}
