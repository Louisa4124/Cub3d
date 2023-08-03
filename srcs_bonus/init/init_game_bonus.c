/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/03 17:01:54 by lboudjem         ###   ########.fr       */
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
	game->pause = 2;
	game->ms = 0;
	game->resolution = 2;
	game->angle_x = -0.1;
	game->plan[0] = NULL;
	game->plan[1] = NULL;
	game->rays = NULL;
	if (rays_create(game))
		return (EXIT_FAILURE);
	if (plane_create(game))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	init_data_thread(t_game *game, t_display data[N_THREAD])
{
	int	i;

	i = 0;
	while (i < N_THREAD)
	{
		data[i].id = i + 1;
		data[i].map = &game->map;
		data[i].pos = &game->pos;
		data[i].rays = game->rays;
		data[i].plan[0] = game->plan[0];
		data[i].plan[1] = game->plan[1];
		data[i].idx_start = i * (game->mlx.win_height / N_THREAD);
		data[i].idx_end[0] = (i + 1) * (game->mlx.win_height / N_THREAD);
		data[i].idx_end[1] = game->mlx.win_width;
		data[i].angle_x = &game->angle_x;
		data[i].angle_z = &game->angle_z;
		data[i].view = &game->view;
		data[i].texture = &game->texture;
		data[i].resolution = &game->resolution;
		++i;
	}
	data[--i].idx_end[0] = game->mlx.win_height;
}
