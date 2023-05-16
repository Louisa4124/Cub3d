/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/05/16 16:01:42 by louisa           ###   ########.fr       */
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

t_vec3d **ft_malloc_rayon(void)
{
	t_vec3d		**rayon;
	int			x;

	x = 0;
	rayon = malloc(sizeof(t_vec3d *) * HEIGHT + 1);
	while (x < HEIGHT)
	{
		rayon[x] = malloc(sizeof(t_vec3d) * WIDTH + 1);
		x++;
	}
	return (rayon);
}

int	key_handler(int key, t_game *game)
{
	if (key == 53 || key == 65307)
		close_event(game);
	return (0);
}

int	ft_win_event(int keycode, t_game *game)
{
	return (0);
}

int	ft_press(int keycode, t_game *game)
{
    printf("key = %d\n", keycode);
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

int	ft_create_plan(t_game *game)
{
	int	x;

	x = 0;
	game->plan = malloc (sizeof(t_plan *) * 2);
	if (!game->plan)
		return (0);
	game->plan[0] = malloc(sizeof(t_plan) * (game->map.y_size + 1));
	if (!game->plan[0])
		return (0);
	game->plan[1] = malloc(sizeof(t_plan) * (game->map.x_size + 1));
	if (!game->plan[1])
		return (0);
	while (x <= game->map.y_size)
	{
		game->plan[0][x].a = 0;
		game->plan[0][x].b = 1;
		game->plan[0][x].c = 0;
		game->plan[0][x].d = -x;
		x++;
	}
	x = 0;
	while (x <= game->map.x_size)
	{
		game->plan[1][x].a = 1;
		game->plan[1][x].b = 0;
		game->plan[1][x].c = 0;
		game->plan[1][x].d = -x;
		x++;
	}
	return (1);
}

void	ft_create_vector(t_game *game)
{
	int		i;
	int		j;
	float	r_h;
	float	r_v;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			r_h = 2 * tan((60 * PI / 180) * 0.5) / WIDTH;
			r_v = 2 * tan((60 * PI / 180) * HEIGHT / (WIDTH * 2)) / HEIGHT;
			game->rays[i][j].x = ((j - WIDTH * 0.5) * r_h);
			game->rays[i][j].y = -1.0;
			game->rays[i][j].z = ((HEIGHT * 0.5 - i) * r_v);
			j++;
		}
		i++;
	}
}

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
	debug_print_map(&game.map);
	ft_init_game(&game);
    game.rays = ft_malloc_rayon();
	game.angle_x = 0;
	game.angle_z = 0;
    ft_create_vector(&game);
	ft_printf("fin vector\n");
	if (ft_create_plan(&game) == 0)
		return (1);
	ft_printf("fin init\n");
	game.view.id = mlx_new_image(game.mlx.ptr, WIDTH, HEIGHT);
	if (game.view.id != NULL)
	{
		game.view.addr = mlx_get_data_addr \
			(game.view.id, &game.view.bpp, &game.view.ll, &game.view.endian);
		//ft_display_game(&game);
        printf("oui\n");
		mlx_loop_hook(game.mlx.ptr, ft_update, &game);
        mlx_hook(game.mlx.win, 2, 1L << 0, ft_press, &game);
		mlx_hook(game.mlx.win, 17, 0L, &close_event, &game);
		mlx_loop(game.mlx.ptr);
	}
	ft_clean_exit(&game, EXIT_FAILURE);
	return (0);
}
