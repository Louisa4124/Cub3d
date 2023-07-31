/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:36:49 by louisa            #+#    #+#             */
/*   Updated: 2023/07/31 11:19:54 by tlegrand         ###   ########.fr       */
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

void	th_print(pthread_mutex_t *m_print, char *str, int id)
{
	pthread_mutex_lock(m_print);
	dprintf(2, "%u ", get_time());
	if (id == 0)
		dprintf(2, "TMAIN : %s\n", str);
	else
		dprintf(2, "T%d : %s\n", id, str);
	pthread_mutex_unlock(m_print);
}

//LOULOU LOULOULOULOULOU EST SUPER FORTE NANMEOH!!!!!!

int	get_status(pthread_mutex_t *mutex, int status)
{
	int	res;
	
	if (pthread_mutex_lock(mutex) != 0)
		return (-1);
	res = status;
	if (pthread_mutex_unlock(mutex) != 0)
		return (-1);
	return (status);
}


void	*routine_queue(void *ptr)
{
	t_thread_data	*th;
	t_job		*job;
	
	th = ptr;
	while (1)
	{
		pthread_mutex_lock(th->m_queue);
		if ((*th->queue)->content == NULL)
		{
			// dprintf(2, "%d : continue\n", get_time());
			pthread_mutex_unlock(th->m_queue);
			// usleep(100);
			continue;
		}
		else
		{
			job = (*th->queue)->content;
			*th->queue = (*th->queue)->next;
			dprintf(2, "%d : T%d jib : %d\n", get_time(), ((t_display *)job->data)->id, job->jib);
			pthread_mutex_unlock(th->m_queue);
		}
		job->func(job->data);
	}
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
		data[i].idx_end[0] = (i + 1) * (game->mlx.win_height / N_THREAD);
		data[i].idx_end[1] = game->mlx.win_width;
		data[i].angle_x = &game->angle_x;
		data[i].angle_z = &game->angle_z;
		data[i].view = &game->view;
		data[i].texture = &game->texture;
		data[i].sem_thread = &game->sem_thread;
		data[i].sem_main = &game->sem_main;
		data[i].m_print = &game->m_print;
		data[i].m_lock = &game->m_lock;
		data[i].lock = &game->lock;
		printf("idx_start %d\n", data[i].idx_start);
		printf("idx_endy %d\n", data[i].idx_end[0]);
		++i;
	}
	data[--i].idx_end[0] = game->mlx.win_height;
	printf("idx_endy last %d\n", data[i].idx_end[0]);
	return (0);
}

t_job	*ft_jobnew(int jib, void *data, void (*func)(t_display *))
{
	t_job	*new;

	new = ft_calloc(1, sizeof(t_job));
	if (!new)
		return (NULL);
	new->jib = jib;
	new->data = data;
	new->func = func;
	return (new);
}

int	init_queue(t_list **head, t_display data[N_THREAD])
{
	int		i;
	t_list	*last;
	t_job	*new_job;
	t_list	*new_node;

	i = 0;
	while (i < N_THREAD)
	{
		new_job = ft_jobnew(i, &data[i], display_game);
		dprintf(2, "i is %d\n", i);
		new_node = ft_lstnew(new_job);
		dprintf(2, "i is %d\n", i);
		ft_lstadd_back(head, new_node);
		dprintf(2, "i is %d\n", i);
		++i;
	}
	ft_lstadd_back(head, ft_lstnew(NULL));
	last = ft_lstlast(*head);
	last->next = *head;
	*head = last;
	
	return (0);
}

void	print_queue(t_list *lst)
{
	lst = lst->next;
	while (lst->content)
	{
		dprintf(2, "jib : %d\tdata addr %p\tfunc addr %p\n", ((t_job *)lst->content)->jib, \
			((t_job *)lst->content)->data, ((t_job *)lst->content)->func);
		dprintf(2, "current addr : %p\nnext addr : %p\n", lst, lst->next);
		lst = lst->next;
	}
	dprintf(2, "content %p\n", lst->content);
	dprintf(2, "current addr : %p\nnext addr : %p\n", lst, lst->next);
}


// TODO: end thread properly, clear sem, clear struct
int	main(int argc, char **argv)
{
	t_game			game;
	t_display		data_display[N_THREAD];
	t_thread_data	data_thread;
	t_list			*queue;
	int				err;
	int				i;

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
	pthread_mutex_init(&game.m_print, NULL);
	pthread_mutex_init(&game.m_lock, NULL);
	pthread_mutex_init(&game.m_queue, NULL);
	game.lock = 0;
	queue = NULL;
	init_data_thread(&game, data_display);
	game.job_queue = &queue;
	init_queue(&queue, data_display);
	data_thread.m_queue = &game.m_queue;
	data_thread.queue = &queue;
	print_queue(*data_thread.queue);
	// exit(1);
	i = 0;
	while (i < N_THREAD)
	{
		if (pthread_create(&game.pid[i], NULL, routine_queue, &data_thread))
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