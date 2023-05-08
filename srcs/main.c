/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/05/08 21:56:28 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

#define width 24
#define height 24

int	ft_man(int num)
{
	if (num == 1)
		printf("Cub3d need a map!\n");
	else if (num > 2)
		printf("Cub3d take only 1 parameter!\n");
	printf("Example : ./cub3D map.cub\n");
	return (0);
}

int	key_handler(int key, t_game *game)
{
	if (key == 53 || key == 65307)
		close_event(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

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
	ft_clean_exit(&game, EXIT_FAILURE);
	/*
	ft_init_game(&game);
	game.mlx->ptr = mlx_init();
	game.mlx->win = mlx_new_window(game.mlx->ptr, W, H, "cub3d");
	game.mlx->image = mlx_new_image(game.mlx->ptr, W, H);
	if (game.mlx->image != NULL)
	{
		game.mlx->addr = mlx_get_data_addr \
			(game.mlx->image, &game.mlx->bpp, &game.mlx->ll, &game.mlx->endian);
		mlx_put_image_to_window(game.mlx->ptr, game.mlx->win, game.mlx->image, 0, 0);
		mlx_hook(game.mlx->win, 2, 1L << 0, &key_handler, &game);
		mlx_hook(game.mlx->win, 17, 0L, &close_event, &game);
		mlx_loop(game.mlx->ptr);
	}
	ft_clean_exit(&game, EXIT_FAILURE);
	*/
	return (0);
}
