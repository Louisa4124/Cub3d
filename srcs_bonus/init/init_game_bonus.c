/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/24 14:36:17 by lboudjem         ###   ########.fr       */
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

	game->rays = malloc(sizeof(t_vec3d *) * game->mlx.win_height + 1);
	if (!game->rays)
		return (EXIT_FAILURE);
	i = 0;
	while (i < game->mlx.win_height)
	{
		game->rays[i] = malloc(sizeof(t_vec3d) * game->mlx.win_width + 1);
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
	game->pause = 2;
	game->ms = 0;
    game->settings = 0;
    game->resolution = 2;
	game->sky.a = 0;
	game->sky.b = 0;
	game->sky.c = 1;
	game->sky.d = -1;
	game->angle_x = -0.1;
	game->r_h = 2 * tan((FOV * PI_DIV_180) * 0.5) / game->mlx.win_width;
	game->r_v = 2 * tan((FOV * PI_DIV_180) * game->mlx.win_height / \
		(game->mlx.win_width * 2)) / game->mlx.win_height;
	game->plan[0] = NULL;
	game->plan[1] = NULL;
	game->rays = NULL;
}

void	ft_init_img(t_game *game)
{
	load_img(game, 0, "img/animation/1.xpm");
	load_img(game, 1, "img/animation/2.xpm");
	load_img(game, 2, "img/animation/3.xpm");
	load_img(game, 3, "img/animation/4.xpm");
	load_img(game, 4, "img/menu/1.xpm");
	load_img(game, 5, "img/menu/2.xpm");
	load_img(game, 6, "img/menu/3.xpm");
	load_img(game, 7, "img/menu/4.xpm");
	load_img(game, 8, "img/settings/1.xpm");
	load_img(game, 9, "img/settings/2.xpm");
	load_img(game, 10, "img/settings/3.xpm");
	load_img(game, 11, "img/settings/4.xpm");
	load_img(game, 12, "img/settings/5.xpm");
	load_img(game, 13, "img/settings/6.xpm");
	load_img(game, 14, "img/settings/7.xpm");
	load_img(game, 15, "img/settings/8.xpm");
	load_img(game, 16, "img/settings/9.xpm");
	load_img(game, 17, "img/settings/10.xpm");
}
