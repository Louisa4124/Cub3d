/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/09/04 14:59:53 by tlegrand         ###   ########.fr       */
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

int	launch_fred(t_game *game, t_thread_data th[N_THREAD])
{
	int	i;

	i = 0;
	while (i < N_THREAD)
	{
		if (pthread_create(&game->pid[i], NULL, routine, &th[i]))
		{
			ft_putstr_fd("Error\nThread creation failed\n", 2);
			game->n_thread = i;
			return (1);
		}
		++i;
	}
	game->n_thread = i;
	return (0);
}

void	debug(t_game *game)
{
	if (DEBUG == 0)
		return ;
	game->pause = 0;
	// game->resolution = 5;
}
	// dprintf(2, "pos igs rand %f %f\n", game->igs[0].pos.x, game->igs[0].pos.y);
	// dprintf(2, "pos igs rand %f %f\n", game->igs[1].pos.x, game->igs[1].pos.y);


//LOULOU LOULOULOULOULOU EST SUPER FORTE NANMEOH!!!!!!
// TODO: end thread properly, clear sem, clear struct
// calculer pout chaque plan a * pos.x + b * pos.y + c * pos.z -d au debut  de chaque frame
int	main(int argc, char **argv)
{
	t_game			game;
	t_thread_data	data_thread[N_THREAD];
	t_job			*queue;

	ft_printf("Bonjour ! Je suis le cub3D de Tilou et j'ai treeees \
		sommeil.... \nShmimimimimi\n rommpshhhhh\n");
	if (argc != 2)
		return (ft_man(argc));
	ft_bzero(&game, sizeof(game));
	if (ft_init_mlx(&game))
		return (EXIT_FAILURE);
	if (parser(argv[1], &game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (ft_init_game(&game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (init_sprite(&game))
		ft_clean_exit(&game, EXIT_FAILURE);
	init_img(&game);
	init_area_link(&game);
	init_igs(&game, game.igs); // a enlever d'ici
	queue = NULL;
	game.queue = &queue;
	init_thread_data(&game, data_thread);
	launch_fred(&game, data_thread);
	update_doors_dist(game.doors, &game.pos, game.n_doors);
	mlx_loop_hook(game.mlx.ptr, update_game, &game);
	mlx_hook(game.mlx.win, 2, 1L << 0, event_press, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, event_unpress, &game);
	mlx_hook(game.mlx.win, 4, 1L << 2, event_pause, &game);
	mlx_hook(game.mlx.win, 6, 1L << 6, event_mouse, &game);
	mlx_hook(game.mlx.win, 8, 1L << 5, event_mouse_reset, &game);
	mlx_hook(game.mlx.win, 17, 0L, close_event, &game);
	mlx_mouse_move(game.mlx.ptr, game.mlx.win, game.mlx.win_width >> 1, \
		game.mlx.win_height >> 1);
	mlx_loop(game.mlx.ptr);
	ft_clean_exit(&game, EXIT_FAILURE);
	return (0);
}

// {0,1,0,-d} plan y 
// (1,0,0,-d) plan x
// plan du sol : {0, 0, 1, 0}
// plan du plafond : {0, 0, 1, -1}
// rays entre -1.000 et 1.000
// NO -> 0
// SO -> 1
// WE -> 2
// EA -> 3

//d = sqrt(2g(z0 - z)) / FPS => gravite que loulou a la flemme d'ajouter
// wall 0=N 1=S 2=W 3=E