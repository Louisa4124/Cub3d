/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/08/02 22:34:18 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	ft_man(int num)
{
	if (num == 1)
		printf("Cub3d need a map!\n");
	else if (num > 2)
		printf("Cub3d take only 1 parameter!\n");
	printf("Example : ./cub3D map.cub\n");
	return (0);
}

// LOULOU LOULOULOULOULOU EST SUPER FORTE NANMEOH!!!!!!

// TODO: end thread properly, clear sem, clear struct
int	main(int argc, char **argv)
{
	t_game		game;
	t_display	data_thread[N_THREAD];
	int			err;

	ft_printf("Bonjour ! Je suis le cub3D de Tilou et j'ai treeees \
		sommeil.... \nShmimimimimi\n rommpshhhhh\n");
	if (argc != 2)
		return (ft_man(argc));
	err = ft_init_mlx(&game);
	if (err)
		return (ft_mlx_error(err));
	if (parser(argv[1], &game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (ft_init_game(&game))
		ft_clean_exit(&game, EXIT_FAILURE);
	game.sprite[0].x = 0;
	game.sprite[0].y = 0;
	game.sprite[0].img = &game.anim[2][0];
	game.sprite[0].frame = 8;

	game.sprite[1].x = 0;
	game.sprite[1].y = 0;
	game.sprite[1].img = &game.anim[3][0];
	game.sprite[1].frame = 10;
	
	game.sprite[2].x = 0;
	game.sprite[2].y = 0;
	game.sprite[2].img = &game.anim[4][0];
	game.sprite[2].frame = 5;

	game.sprite[3].x = 0;
	game.sprite[3].y = 0;
	game.sprite[3].img = &game.anim[2][1];
	game.sprite[3].frame = 6;

	game.sprite[4].x = 0;
	game.sprite[4].y = 0;
	game.sprite[4].img = &game.anim[4][1];
	game.sprite[4].frame = 6;

	game.sprite[5].x = 0;
	game.sprite[5].y = 0;
	game.sprite[5].img = &game.anim[3][1];
	game.sprite[5].frame = 6;
	ft_init_img(&game);
	init_data_thread(&game, data_thread);
	game.th = data_thread;
	mlx_loop_hook(game.mlx.ptr, update_game, &game);
	mlx_hook(game.mlx.win, 2, 1L << 0, event_press, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, event_unpress, &game);
	mlx_hook(game.mlx.win, 4, 1L << 2, event_pause, &game);
	mlx_hook(game.mlx.win, 17, 0L, close_event, &game);
	mlx_loop(game.mlx.ptr);
	ft_clean_exit(&game, EXIT_FAILURE);
	return (0);
}

// plan du sol : {0, 0, 1, 0}
// plan du plafond : {0, 0, 1, -1}
// rays entre -1.000 et 1.000
// NO -> 0
// SO -> 1
// WE -> 2
// EA -> 3

//d = sqrt(2g(z0 - z)) / FPS => gravite que loulou a la flemme d'ajouter