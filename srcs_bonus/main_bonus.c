/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/08/03 23:04:31 by tlegrand         ###   ########.fr       */
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

int	mimimain(int argc, char **argv)
{
	t_game			game;
	t_thread_data	data_thread[N_THREAD];
	t_job			*queue;

	if (argc != 2)
		return (ft_man(argc));
	if (ft_init_mlx(&game))
		return (1);
	if (parser(argv[1], &game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (ft_init_game(&game))
		ft_clean_exit(&game, EXIT_FAILURE);
	init_area_link(&game);
	queue = NULL;
	game.queue = &queue;
	init_thread_data(&game, data_thread);
	return (0);
}

int	launch_fred(t_game *game, t_thread_data th[N_THREAD])
{
	int	i;

	i = 0;
	while (i < N_THREAD)
	{
		if (pthread_create(&game->pid[i], NULL, routine_queue, &th[i]))
		{
			ft_putstr_fd("Error\nThread creation failed\n", 2);
			game->n_thread = i;
			return (i);
		}
		++i;
	}
	return (0);
}

//LOULOU LOULOULOULOULOU EST SUPER FORTE NANMEOH!!!!!!
// TODO: end thread properly, clear sem, clear struct
int	main(int argc, char **argv)
{
	t_game			game;
	t_thread_data	data_thread[N_THREAD];
	t_job			*queue;

	ft_printf("Bonjour ! Je suis le cub3D de Tilou et j'ai treeees \
		sommeil.... \nShmimimimimi\n rommpshhhhh\n");
	if (argc != 2)
		return (ft_man(argc));
	if (ft_init_mlx(&game))
		return (1);
	if (load_pause(&game) == 1)
		return (1);
	if (parser(argv[1], &game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (ft_init_game(&game))
		ft_clean_exit(&game, EXIT_FAILURE);
	init_area_link(&game);
	queue = NULL;
	game.queue = &queue;
	init_thread_data(&game, data_thread);
	if (launch_fred(&game, data_thread))
		ft_clean_exit(&game, EXIT_FAILURE);
	mlx_loop_hook(game.mlx.ptr, update_game, &game);
	mlx_hook(game.mlx.win, 2, 1L << 0, event_press, &game);
	mlx_hook(game.mlx.win, 4, 1L << 2, event_pause, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, event_unpress, &game);
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