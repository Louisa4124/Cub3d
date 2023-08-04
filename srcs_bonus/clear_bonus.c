/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:34:52 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/04 21:49:08 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	s_mlx_destroy(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
}

void	s_img_destroy(t_mlx *mlx, t_img *img)
{
	if (img->id)
		mlx_destroy_image(mlx->ptr, img->id);
	img->id = NULL;
	img->addr = NULL;
}

void	destroy_texture(t_mlx *mlx, t_texture *texture)
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

void	destroy_sprite(t_mlx *mlx, t_sprite *sprite, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (sprite[i].img.id)
		{
			mlx_destroy_image(mlx->ptr, sprite[i].img.id);
			sprite[i].img.id = NULL;
			sprite[i].img.addr = NULL;
		}
	}
}

void	ft_clean_exit(t_game *game, int exit_code)
{
	int	i;

	change_status(&game->m_queue, &game->queue_status, 1);
	i = -1;
	while (++i < N_THREAD)
		sem_post(&game->sem_thread);
	i = -1;
	while (++i < game->n_thread)
		pthread_join(game->pid[i], NULL);
	sem_destroy(&game->sem_thread);
	sem_destroy(&game->sem_main);
	clear_job(game->queue);
	destroy_texture(&game->mlx, &game->texture);
	destroy_sprite(&game->mlx, game->sprite, N_SPRITE);
	s_mlx_destroy(&game->mlx);
	ft_free2d((void **) game->map.layout, game->map.y_size);
	ft_free_secure(game->plan[0]);
	ft_free_secure(game->plan[1]);
	ft_free2d((void **) game->rays, game->mlx.win_height);
	ft_printf("\n");
	exit(exit_code);
}
