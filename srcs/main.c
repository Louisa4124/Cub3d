/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/05/19 16:02:27 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_man(int num)
{
	if (num == 1)
		printf("Cub3d need a map!\n");
	else if (num > 2)
		printf("Cub3d take only 1 parameter!\n");
	printf("Example : ./cub3D map.cub\n");
	return (0);
}

t_vec3d	**ft_malloc_rayon(t_game *game)
{
	t_vec3d		**rayon;
	int			x;

	x = 0;
	rayon = malloc(sizeof(t_vec3d *) * game->mlx.win_height + 1);
	while (x < game->mlx.win_height)
	{
		rayon[x] = malloc(sizeof(t_vec3d) * game->mlx.win_width + 1);
		x++;
	}
	return (rayon);
}


int	ft_win_event(int keycode, t_game *game)
{
	return (0);
}

int	ft_press(int keycode, t_game *game)
{
	if (keycode == 53 || keycode == 65307)
		close_event(game);
	if (keycode == 65362)
		game->pos.y -= 0.5;
	if (keycode == 65364)
		game->pos.y += 0.5;
	if (keycode == EVENT_D)
		game->pos.x -= 0.5;
	if (keycode == EVENT_D)
		game->pos.x += 0.5;
	if (keycode == 65363)
		game->angle_z += 0.07;
	if (keycode == 65361)
		game->angle_z -= 0.07;
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	if (game->angle_z <= -PI * 2)
		game->angle_z += PI * 2;
	return (0);
}

int	ft_unpress(int keycode, t_game *game)
{
	return (0);
}

void	ft_create_vector(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->mlx.win_height)
	{
		j = 0;
		while (j < game->mlx.win_width)
		{
			game->rays[i][j].x = ((j - game->mlx.win_width * 0.5) * game->r_h);
			game->rays[i][j].y = -1.0;
			game->rays[i][j].z = ((game->mlx.win_height * 0.5 - i) * game->r_h);
			j++;
		}
		i++;
	}
}

//LOULOU EST SUPER FORTE NANMEOH!!!!!!

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	if (argc != 2)
		return (ft_man(argc));
	if (ft_init_mlx(&game))
		return (1);
	s_map_init(&game.map);
	s_img_init(&game.texture.north);
	s_img_init(&game.texture.south);
	s_img_init(&game.texture.east);
	s_img_init(&game.texture.west);
	if (parser(argv[1], &game))
		return (1);
	debug_print_texture(&game.texture);
	ft_init_game(&game);
    game.rays = ft_malloc_rayon(&game);
	game.angle_x = 0;
	game.angle_z = 0;
    ft_create_vector(&game);
	if (ft_creat_plans(&game) == 0)
		return (1);
	game.view.id = mlx_new_image(game.mlx.ptr, game.mlx.win_width, game.mlx.win_height);
	if (game.view.id != NULL)
	{
		game.view.addr = mlx_get_data_addr \
			(game.view.id, &game.view.bpp, &game.view.ll, &game.view.endian);
		//ft_display_game(&game);
		mlx_loop_hook(game.mlx.ptr, ft_update, &game);
        mlx_hook(game.mlx.win, 2, 1L << 0, ft_press, &game);
		mlx_hook(game.mlx.win, 17, 0L, &close_event, &game);
		mlx_loop(game.mlx.ptr);
	}
	ft_clean_exit(&game, EXIT_FAILURE);
	return (0);
}
