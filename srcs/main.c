/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/05/16 13:21:05 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int map[WIDTH][HEIGHT]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}	
};

int	ft_man(int num)
{
	if (num == 1)
		printf("Cub3d need a map!\n");
	else if (num > 2)
		printf("Cub3d take only 1 parameter!\n");
	printf("Example : ./cub3D map.cub\n");
	return (0);
}

// int	key_handler(int key, t_game *game)
// {
// 	if (key == 53 || key == 65307)
// 		close_event(game);
// 	return (0);
// }

void	my_mlx_pixel_put(t_img *img, const int x, const int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	**ft_malloc_map(void)
{
	int		**map;
	int		x;

	x = 0;
	map = ft_calloc(sizeof(int **), (H + 1));
	while (x < H)
	{
		map[x] = ft_calloc(sizeof(int *), (W + 1));
		x++;
	}
	return (map);
}

void	ft_display(t_game *game)
{
	int				i;
	int				j;
	t_vec3d			inter;

	j = -1;
	while (++j < H)
	{
		i = -1;
		while (++i < W)
		{
			ft_rotate_vec_z(game->rays[j][i], PI/2);
			if (ft_inter_plan_line(game, &game->plan[0][0], &inter, j, i) == 0)
				my_mlx_pixel_put(&game->view, i, j, RED);
			else if (ft_inter_plan_line(game, &game->plan[0][1], &inter, j, i) == 0)
				my_mlx_pixel_put(&game->view, i, j, WHITE);
			else if (ft_inter_plan_line(game, &game->plan[1][0], &inter, j, i) == 0)
				my_mlx_pixel_put(&game->view, i, j, GREEN);
			else if (ft_inter_plan_line(game, &game->plan[1][1], &inter, j, i) == 0)
				my_mlx_pixel_put(&game->view, i, j, BLUE);
		}
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
}

void	ft_get_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (game->map[y][x] == 5)
			{
				game->pos.x = x;
				game->pos.y = y;
			}
			x++;
		}
		y++;
	}
}

int	ft_create_plan(t_game *game)
{
	int	x;

	x = 0;
	game->plan = malloc (sizeof(t_plan *) * 2);
	if (!game->plan)
		return (0);
	game->plan[0] = malloc(sizeof(t_plan) * (HEIGHT + 1));
	if (!game->plan[0])
		return (0);
	game->plan[1] = malloc(sizeof(t_plan) * (WIDTH + 1));
	if (!game->plan[1])
		return (0);
	while (x <= HEIGHT)
	{
		game->plan[0][x].a = 0;
		game->plan[0][x].b = 1;
		game->plan[0][x].c = 0;
		game->plan[0][x].d = -x;
		x++;
	}
	x = 0;
	while (x <= WIDTH)
	{
		game->plan[1][x].a = 1;
		game->plan[1][x].b = 0;
		game->plan[1][x].c = 0;
		game->plan[1][x].d = -x;
		x++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	if (argc != 2)
		return (ft_man(argc));
	if (ft_init_mlx(&game))
		return (1);
	//s_map_init(&game.map);
	s_img_init(&game.texture.north);
	s_img_init(&game.texture.south);
	s_img_init(&game.texture.east);
	s_img_init(&game.texture.west);
	s_img_init(&game.view);
	game.rays = ft_malloc_rays();
	ft_init_rays(&game);
	ft_init_game(&game);
	ft_create_plan(&game);
	//ft_creat_plan_v(&game);
	game.map = ft_malloc_map();
    for (int x = 0; x < HEIGHT; x++)
    {
        for (int y = 0; y < WIDTH; y++)
        {
            game.map[x][y] = map[x][y];
            printf("%d ", game.map[x][y]);
        }
        printf("\n");
    }
	if (parser(argv[1], &game))
		return (1);
	game.view.id = mlx_new_image(game.mlx.ptr, W, H);
	if (game.view.id != NULL)
	{
		game.view.addr = mlx_get_data_addr \
			(game.view.id, &game.view.bpp, &game.view.ll, &game.view.endian);
		//ft_display(&game);
		//ft_display_game(&game);
        ft_get_pos(&game);
        printf("x = %f\n", game.pos.x);
        printf("y = %f\n", game.pos.y);
		mlx_put_image_to_window(game.mlx.ptr, game.mlx.win, \
			game.view.id, 0, 0);
		mlx_loop_hook(game.mlx.ptr, ft_update, &game);
		mlx_hook(game.mlx.win, 2, 1L << 0, &key_handler, &game);
		mlx_hook(game.mlx.win, 17, 0L, &close_event, &game);
		mlx_loop(game.mlx.ptr);
	}
	ft_clean_exit(&game, EXIT_FAILURE);

	return (0);
}
