/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:34:52 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/01 14:50:15 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	s_mlx_destroy(t_game *game)
{
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.ptr, game->mlx.win);
	if (game->mlx.ptr)
	{
		mlx_destroy_display(game->mlx.ptr);
		free(game->mlx.ptr);
	}
}

void	s_img_destroy(t_mlx *mlx, t_img *img)
{
	if (img->id)
		mlx_destroy_image(mlx->ptr, img->id);
	img->id = NULL;
	img->addr = NULL;
}

void	ft_destroy_texture(t_mlx *mlx, t_texture *texture)
{
	s_img_destroy(mlx, &texture->wall[0]);
	s_img_destroy(mlx, &texture->wall[1]);
	s_img_destroy(mlx, &texture->wall[2]);
	s_img_destroy(mlx, &texture->wall[3]);
}

int	change_status(pthread_mutex_t *mutex, int *status, int new_status)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (-1);
	*status = new_status;
	if (pthread_mutex_unlock(mutex) != 0)
		return (-1);
	return (0);
}


void	ft_clean_exit(t_game *game, int exit_code)
{
	int	i;

	change_status(&game->m_queue, &game->queue_status, 1);
	i = -1;
	while (++i < N_THREAD)
		sem_post(&game->sem_thread);
	i = -1;
	while (++i < N_THREAD)
		pthread_join(game->pid[i], NULL);
	sem_destroy(&game->sem_thread);
	sem_destroy(&game->sem_main);
	pthread_mutex_destroy(&game->m_print);
	ft_destroy_texture(&game->mlx, &game->texture);
	s_mlx_destroy(game);
	ft_free2d((void **) game->map.layout, game->map.y_size);
	ft_free_secure(game->plan[0]);
	ft_free_secure(game->plan[1]);
	ft_free2d((void **) game->rays, game->mlx.win_height);
	exit(exit_code);
}
