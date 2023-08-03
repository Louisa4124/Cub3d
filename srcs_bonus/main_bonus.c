/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/08/03 14:11:57 by tlegrand         ###   ########.fr       */
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

void	th_print(pthread_mutex_t *m_print, char *str, int id)
{
	pthread_mutex_lock(m_print);
	dprintf(2, "%u ", get_time());
	if (id == 0)
		dprintf(2, "TMAIN : %s\n", str);
	else
		dprintf(2, "T%d : %s\n", id, str);
	pthread_mutex_unlock(m_print);
}

//LOULOU LOULOULOULOULOU EST SUPER FORTE NANMEOH!!!!!!

int	get_status(pthread_mutex_t *mutex, int status)
{
	int	res;
	
	if (pthread_mutex_lock(mutex) != 0)
		return (-1);
	res = status;
	if (pthread_mutex_unlock(mutex) != 0)
		return (-1);
	return (status);
}

// TODO: end thread properly, clear sem, clear struct
int	main(int argc, char **argv)
{
	t_game			game;
	t_thread_data	data_thread[N_THREAD];
	t_list			*queue;
	int				err;
	int				i;

	ft_printf("Bonjour ! Je suis le cub3D de Tilou et j'ai treeees \
		sommeil.... \nShmimimimimi\n rommpshhhhh\n");
	if (argc != 2)
		return (ft_man(argc));
	err = ft_init_mlx(&game);
	if (err)
		return (ft_mlx_error(err));
	if (load_pause(&game) == 1)
		return (1);
	if (parser(argv[1], &game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (ft_init_game(&game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (sem_init(&game.sem_thread, 0, 0) == -1)
		dprintf(2, "Error sem_init\n");
	if (sem_init(&game.sem_main, 0, 0) == -1)
		dprintf(2, "Error sem_init\n");
	pthread_mutex_init(&game.m_print, NULL);
	pthread_mutex_init(&game.m_queue, NULL);
	sem_init(&game.sem_main, 0, 0);
	sem_init(&game.sem_thread, 0, 0);
	queue = NULL;
	init_area_link(&game);
	game.job_queue = &queue;
	init_queue(&queue, &game.link, game.area);
	init_thread_data(&game, data_thread);
	// debug_print_queue(*data_thread[0].queue);
	i = 0;
	while (i < N_THREAD)
	{
		if (pthread_create(&game.pid[i], NULL, routine_queue, &data_thread[i]))
			dprintf(2, " ER THR\n");
		++i;
	}
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