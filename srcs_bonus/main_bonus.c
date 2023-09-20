/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/09/20 12:30:56 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

static int	ft_man(int num)
{
	if (num == 1)
		ft_printf("Cub3d need a map!\n");
	else if (num > 2)
		ft_printf("Cub3d take only 1 parameter!\n");
	ft_printf("Example : ./cub3D map.cub\n");
	return (0);
}

static void	initialization(t_game *game, t_thread_data data_th[N_THREAD], \
	char *pathname)
{
	if (ft_init_mlx(game))
		ft_clean_exit(game, EXIT_FAILURE);
	if (parser(pathname, game))
		ft_clean_exit(game, EXIT_FAILURE);
	if (ft_init_game(game))
		ft_clean_exit(game, EXIT_FAILURE);
	if (init_img(game))
		ft_clean_exit(game, EXIT_FAILURE);
	init_thread_data(game, data_th);
	if (launch_thread(game, data_th))
		ft_clean_exit(game, EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game			game;
	t_thread_data	data_thread[N_THREAD];
	t_job			*queue;

	if (argc != 2)
		return (ft_man(argc));
	ft_bzero(&game, sizeof(game));
	queue = NULL;
	game.queue = &queue;
	initialization(&game, data_thread, argv[1]);
	set_mlx_hook(&game);
	mlx_mouse_move(game.mlx.ptr, game.mlx.win, game.mlx.win_width >> 1, \
		game.mlx.win_height >> 1);
	mlx_loop(game.mlx.ptr);
	return (0);
}
