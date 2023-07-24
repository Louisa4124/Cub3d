/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/24 22:21:14 by tlegrand         ###   ########.fr       */
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

int	ft_init_airplane(t_game *game)
{
	if (rays_create(game))
		return (EXIT_FAILURE);
	if (plane_create(game))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_init_game(t_game *game)
{
	game->bit_key = 0;
	game->pause = 0;
	game->angle_x = -0.1;
	game->plan[0] = NULL;
	game->plan[1] = NULL;
	game->rays = NULL;
}
