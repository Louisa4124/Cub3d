/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/09/17 15:57:44 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	plane_create(t_game *game)
{
	int	i;

	game->plan[0] = ft_calloc((game->map.y_size + 1), sizeof(t_plan));
	game->plan[1] = ft_calloc((game->map.x_size + 1), sizeof(t_plan));
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

	game->rays = ft_calloc(game->mlx.win_height, sizeof(t_vec3d *));
	if (!game->rays)
		return (EXIT_FAILURE);
	i = 0;
	while (i < game->mlx.win_height)
	{
		game->rays[i] = ft_calloc(game->mlx.win_width, sizeof(t_vec3d));
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

void	init_area(t_game *game)
{
	int	i;

	i = -1;
	while (++i < N_CHUNK)
	{
		game->area[i].start_y = i * (game->mlx.win_height / N_CHUNK);
		game->area[i].end_y = (i + 1) * (game->mlx.win_height / N_CHUNK);
		game->area[i].start_x = 0;
		game->area[i].end_x = game->mlx.win_width;
	}
	game->area[--i].end_y = game->mlx.win_height;
}

void	init_link(t_game *game)
{
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
	game->link.resolution = &game->resolution;
	game->link.light = &game->light;
	game->link.igs = game->igs;
	game->link.door = game->doors;
	game->link.n_doors = &game->n_doors;
}

int	ft_init_game(t_game *game)
{
	game->pause = 2;
	game->player = 1;
	game->jump = 0;
	game->angle_offset = ANG_OFFSET_MOUSE;
	game->mouse = (t_vec2d){game->mlx.win_width >> 1, \
		game->mlx.win_height >> 1};
	game->resolution = 3;
	game->light = 1;
	game->minimap_size = 10;
	game->sensitivity = 0.5;
	if (rays_create(game) || plane_create(game))
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), EXIT_FAILURE);
	if (sem_init(&game->sem_thread, 0, 0) == -1)
		return (ft_putstr_fd("Error\nSem_init failed\n", 2), EXIT_FAILURE);
	if (sem_init(&game->sem_main, 0, 0) == -1)
		return (ft_putstr_fd("Error\nSem_init failed\n", 2), EXIT_FAILURE);
	if (pthread_mutex_init(&game->m_queue, NULL))
		return (ft_putstr_fd("Error\nMutex_init failed\n", 2), EXIT_FAILURE);
	game->view_data_cpy = ft_calloc(sizeof(char), game->view.height * \
		game->view.ll);
	if (game->view_data_cpy == NULL)
		return (ft_putstr_fd("Error\nMaloc failed\n", 2), EXIT_FAILURE);
	init_area(game);
	init_link(game);
	return (EXIT_SUCCESS);
}
