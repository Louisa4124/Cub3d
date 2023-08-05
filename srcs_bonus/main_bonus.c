/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/08/05 13:41:54 by tlegrand         ###   ########.fr       */
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

void	sizegame(t_game *game)
{
	dprintf(2, "sizeof(game->button) is %lu\n", sizeof(game->button));
	dprintf(2, "sizeof(game->animation) is %lu\n", sizeof(game->animation));
	dprintf(2, "sizeof(game->anim) is %lu\n", sizeof(game->anim));
	dprintf(2, "sizeof(game->image) is %lu\n", sizeof(game->image));
	dprintf(2, "sizeof(game->sprite) is %lu\n", sizeof(game->sprite));
	dprintf(2, "sizeof(game->mouse) is %lu\n", sizeof(game->mouse));
	dprintf(2, "sizeof(game->transparent) is %lu\n", sizeof(game->transparent));
	dprintf(2, "sizeof(game->ms) is %lu\n", sizeof(game->ms));
	dprintf(2, "sizeof(game->pause) is %lu\n", sizeof(game->pause));
	dprintf(2, "sizeof(game->map) is %lu\n", sizeof(game->map));
	dprintf(2, "sizeof(game->mlx) is %lu\n", sizeof(game->mlx));
	dprintf(2, "sizeof(game->pos) is %lu\n", sizeof(game->pos));
	dprintf(2, "sizeof(game->rays) is %lu\n", sizeof(game->rays));
	dprintf(2, "sizeof(game->plan) is %lu\n", sizeof(game->plan));
	dprintf(2, "sizeof(game->texture) is %lu\n", sizeof(game->texture));
	dprintf(2, "sizeof(game->sem_thread) is %lu\n", sizeof(game->sem_thread));
	dprintf(2, "sizeof(game->link) is %lu\n", sizeof(game->link));
	dprintf(2, "sizeof(game->area) is %lu\n", sizeof(game->area));
	dprintf(2, "sizeof(game->pid) is %lu\n", sizeof(game->pid));
	dprintf(2, "sizeof(game->m_queue) is %lu\n", sizeof(game->m_queue));
	dprintf(2, "sizeof(game->queue) is %lu\n", sizeof(game->queue));
	exit(0);
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
	ft_bzero(&game, sizeof(game));
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
	launch_fred(&game, data_thread);
	init_img(&game);
	if (init_sprite(&game))
		ft_clean_exit(&game, EXIT_FAILURE);
	init_sprite_fill(&game);
	mlx_loop_hook(game.mlx.ptr, update_game, &game);
	mlx_hook(game.mlx.win, 2, 1L << 0, event_press, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, event_unpress, &game);
	mlx_hook(game.mlx.win, 4, 1L << 2, event_pause, &game);
	mlx_hook(game.mlx.win, 6, 1L << 6, event_mouse, &game);
	mlx_hook(game.mlx.win, 8, 1L << 5, event_mouse_reset, &game);
	mlx_hook(game.mlx.win, 17, 0L, close_event, &game);
	mlx_mouse_hide(game.mlx.ptr, game.mlx.win);
	mlx_mouse_move(game.mlx.ptr, game.mlx.win, game.mlx.win_width >> 1, \
		game.mlx.win_height >> 1);
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