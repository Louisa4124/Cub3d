/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/10/04 13:24:07 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	plane_create(t_game *game)
{
	int	i;

	game->plan[0] = ft_calloc(game->map.y_size + 1, sizeof(t_plan));
	game->plan[1] = ft_calloc(game->map.x_size + 1, sizeof(t_plan));
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

	game->rays = ft_calloc(game->mlx.win_height + 1, sizeof(t_vec3d *));
	if (!game->rays)
		return (EXIT_FAILURE);
	i = 0;
	while (i < game->mlx.win_height)
	{
		game->rays[i] = ft_calloc(game->mlx.win_width + 1, sizeof(t_vec3d));
		if (!game->rays[i])
			return (EXIT_FAILURE);
		j = 0;
		while (j < game->mlx.win_width)
		{
			game->rays[i][j].x = ((j - game->mlx.win_width * 0.5) * game->r_h);
			game->rays[i][j].y = -1.0;
			game->rays[i][j].z = ((game->mlx.win_height * 0.5 - i) * game->r_v);
			++j;
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_init_game(t_game *game)
{
	game->angle_x = -0.1;
	game->r_h = 2 * tan((FOV * PI_DIV_180) * 0.5) / game->mlx.win_width;
	game->r_v = 2 * tan((FOV * PI_DIV_180) * game->mlx.win_height / \
		(game->mlx.win_width * 2)) / game->mlx.win_height;
	if (rays_create(game) || plane_create(game))
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
