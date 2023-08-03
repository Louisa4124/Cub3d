/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:21:09 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/03 21:21:17 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	init_queue(t_job **head, t_link *link, t_area area[N_CHUNK], t_game *game)
{
	int		i;
	t_job	*last;
	t_job	*new_job;

	i = 0;
	while (i < N_CHUNK)
	{
		if (add_job(head, link, &area[i], display_game))
			return (1);
		++i;
	}
	if (add_job(head, link, &game->minimap_size, draw_map))
		return (1);
	if (add_job(head, NULL, NULL, NULL))
		return (1);
	last = joblast(*head);
	last->jid = -1;
	last->next = *head;
	*head = last;
	return (0);
}

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

void	*routine_queue(void *ptr)
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
		if ((*th->queue)->jid == -1)
		{
			dprintf(2, "%u : continue\n", get_time());
			pthread_mutex_unlock(th->m_queue);
			continue ;
		}
		else
		{
			job = (*th->queue);
			*th->queue = (*th->queue)->next;
			// dprintf(2, "%d : T%d jid : %d\n", get_time(), th->tid, job->jid);
			pthread_mutex_unlock(th->m_queue);
		}
		job->func(job->data, job->area);
		sem_post(th->sem_main);
	}
	// dprintf(2, "T%d QUIT\n", th->tid);
	return (NULL);
}
