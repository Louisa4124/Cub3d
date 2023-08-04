/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:21:09 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/04 11:46:55 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

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
