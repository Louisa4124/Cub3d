/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:21:09 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/03 13:42:39 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

t_job	*ft_jobnew(int jib, void *data, t_area *area, \
	void (*func)(void *, t_area *))
{
	t_job	*new;

	new = ft_calloc(1, sizeof(t_job));
	if (!new)
		return (NULL);
	new->jib = jib;
	new->data = data;
	new->area = area;
	new->func = func;
	return (new);
}

int	init_queue(t_list **head, t_display data[N_CHUNK], t_area area[N_CHUNK])
{
	int		i;
	t_list	*last;
	t_job	*new_job;
	t_list	*new_node;

	i = 0;
	while (i < N_CHUNK)
	{
		new_job = ft_jobnew(i, &data[i], &area[i], display_game);
		new_node = ft_lstnew(new_job);
		ft_lstadd_back(head, new_node);
		++i;
	}
	ft_lstadd_back(head, ft_lstnew(NULL));
	last = ft_lstlast(*head);
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
		data[i].queue = game->job_queue;
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
		if ((*th->queue)->content == NULL)
		{
			dprintf(2, "%u : continue\n", get_time());
			pthread_mutex_unlock(th->m_queue);
			continue ;
		}
		else
		{
			job = (*th->queue)->content;
			*th->queue = (*th->queue)->next;
			// dprintf(2, "%d : T%d jib : %d\n", get_time(), th->tid, job->jib);
			pthread_mutex_unlock(th->m_queue);
		}
		job->func(job->data, job->area);
		sem_post(th->sem_main);
	}
	// dprintf(2, "T%d QUIT\n", th->tid);
	return (NULL);
}
