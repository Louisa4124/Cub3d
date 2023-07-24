/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/07/24 22:44:28 by tlegrand         ###   ########.fr       */
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

//LOULOU LOULOULOULOULOU EST SUPER FORTE NANMEOH!!!!!!

void	*routine(void *data)
{
	t_display	*data_th;

	data_th = data;
	while (1)
	{
		sem_wait(data_th->sem_thread);
		dprintf(2, "T%d h start draw\n", data_th->id);
		display_game(data_th);
		dprintf(2, "T%d end draw\n", data_th->id);
		sem_post(data_th->sem_main);
	}
	return (NULL);
}

int	init_data_thread(t_game *game, t_display data[N_THREAD])
{
	int	i;

	i = 0;
	while (i < N_THREAD)
	{
		data[i].id = i + 1;
		data[i].map = &game->map;
		data[i].pos = &game->pos;
		data[i].rays = game->rays;
		data[i].plan[0] = game->plan[0];
		data[i].plan[1] = game->plan[1];
		data[i].idx_start = i * (game->mlx.win_height / N_THREAD);
		data[i].idx_end[0] = (i + 1) * (game->mlx.win_height / N_THREAD) - 1;
		data[i].idx_end[1] = game->mlx.win_width;
		data[i].angle_x = &game->angle_x;
		data[i].angle_z = &game->angle_z;
		data[i].view = &game->view;
		data[i].texture = &game->texture;
		data[i].sem_thread = &game->sem_thread;
		data[i].sem_main = &game->sem_main;
		printf("idx_start %d\n", data[i].idx_start);
		printf("idx_endy %d\n", data[i].idx_end[0]);
		printf("idx_endx %d\n", data[i].idx_end[1]);
		++i;
	}
	return (0);
}


// TODO: end thread properly, clear sem
int	main(int argc, char **argv)
{
	t_game		game;
	t_display	data_thread[N_THREAD];
	int		err;
	int		i;

	ft_printf("Bonjour ! Je suis le cub3D de Tilou et j'ai treeees \
		sommeil.... \nShmimimimimi\n rommpshhhhh\n");
	if (argc != 2)
		return (ft_man(argc));
	err = ft_init_mlx(&game);
	if (err)
		return (ft_mlx_error(err));
	ft_init_game(&game);
	if (load_pause(&game) == 1)
		return (1);
	if (parser(argv[1], &game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (ft_init_airplane(&game))
		ft_clean_exit(&game, EXIT_FAILURE);
	if (sem_init(&game.sem_thread, 0, 0) == -1)
		dprintf(2, "Error sem_init\n");
	if (sem_init(&game.sem_main, 0, 0) == -1)
		dprintf(2, "Error sem_init\n");
	init_data_thread(&game, data_thread);
	// exit(1);
	i = 0;
	while (i < N_THREAD)
	{
		if (pthread_create(&game.pid[i], NULL, routine, &data_thread[i]))
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