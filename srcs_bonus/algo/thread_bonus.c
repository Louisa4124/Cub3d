/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:21:09 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/19 20:47:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	init_thread_data( t_game *game, t_thread_data data[N_THREAD])
{
	int	i;

	i = 0;
	while (i < N_THREAD)
	{
		data[i].tid = i + 1;
		data[i].sem_main = &game->sem_main;
		data[i].sem_thread = &game->sem_thread;
		data[i].m_queue = &game->m_queue;
		data[i].queue_status = &game->queue_status;
		data[i].queue = game->queue;
		++i;
	}
}

void	*routine(void *ptr)
{
	t_thread_data	*th;
	t_job			*job;

	th = ptr;
	while (1)
	{
		sem_wait(th->sem_thread);
		pthread_mutex_lock(th->m_queue);
		if (*th->queue_status == 1)
		{
			pthread_mutex_unlock(th->m_queue);
			break ;
		}
		job = (*th->queue);
		*th->queue = (*th->queue)->next;
		pthread_mutex_unlock(th->m_queue);
		job->func(job->data, job->area);
		free(job);
		sem_post(th->sem_main);
	}
	return (NULL);
}

void	thread_anim(void *ptr, void *area)
{
	t_sprite	*sprite;
	t_vec2d		*pos;

	sprite = ptr;
	pos = area;
	if (sprite->axis == 0)
	{
		if (*sprite->ms >= 0.02)
			sprite->y += sprite->ry;
		if (sprite->y >= sprite->ry * sprite->frame)
			sprite->y = 0;
	}
	else
	{
		if (*sprite->ms >= 0.02)
			sprite->x += sprite->rx;
		if (sprite->x >= sprite->rx * sprite->frame)
			sprite->x = 0;
	}
	draw_on(sprite->view, (t_vec2d){pos->x, pos->y}, sprite->img, \
		(t_area){sprite->x, sprite->x + sprite->rx, sprite->y, \
		sprite->y + sprite->ry});
}

int	launch_thread(t_game *game, t_thread_data th[N_THREAD])
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
