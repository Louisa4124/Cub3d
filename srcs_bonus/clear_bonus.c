/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:34:52 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/19 20:40:52 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	s_img_destroy(t_mlx *mlx, t_img *img)
{
	if (img->id)
		mlx_destroy_image(mlx->ptr, img->id);
	img->id = NULL;
	img->addr = NULL;
}

static void	s_destroy_texture(t_mlx *mlx, t_texture *texture)
{
	s_img_destroy(mlx, &texture->wall[0]);
	s_img_destroy(mlx, &texture->wall[1]);
	s_img_destroy(mlx, &texture->wall[2]);
	s_img_destroy(mlx, &texture->wall[3]);
	s_img_destroy(mlx, &texture->t_ceiling);
	s_img_destroy(mlx, &texture->t_floor);
	s_img_destroy(mlx, &texture->t_door);
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

static void	s_destroy_all_img(t_mlx *mlx, t_sprite *sprite, t_img tab[5][23])
{
	int	i;
	int	j;

	i = -1;
	while (++i < N_SPRITE)
		s_img_destroy(mlx, &sprite[i].img);
	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 23)
			s_img_destroy(mlx, &tab[i][j]);
	}
}

void	ft_clean_exit(t_game *game, int exit_code)
{
	int	i;

	change_status(&game->m_queue, &game->queue_status, 1);
	i = -1;
	while (++i < game->n_thread)
		sem_post(&game->sem_thread);
	i = -1;
	while (++i < game->n_thread)
		pthread_join(game->pid[i], NULL);
	sem_destroy(&game->sem_thread);
	sem_destroy(&game->sem_main);
	clear_job(game->queue);
	s_destroy_texture(&game->mlx, &game->texture);
	s_destroy_all_img(&game->mlx, game->sprite, game->anim);
	s_img_destroy(&game->mlx, &game->view);
	ft_free_secure(game->view_data_cpy);
	better_mlx_mouse_show(game->mlx.ptr, game->mlx.win, &game->cursor);
	s_mlx_destroy(&game->mlx);
	ft_free2d((void **) game->map.layout, game->map.y_size);
	ft_free_secure(game->doors);
	ft_free_secure(game->plan[0]);
	ft_free_secure(game->plan[1]);
	ft_free2d((void **) game->rays, game->mlx.win_height);
	ft_printf("\n");
	exit(exit_code);
}
