/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:29:11 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/21 15:15:26 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	wait_job(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->n_job)
		sem_post(&game->sem_thread);
	i = -1;
	while (++i < game->n_job)
		sem_wait(&game->sem_main);
	game->n_job = 0;
	return (0);
}

int	send_frame_job(t_game *game)
{
	int		i;

	i = 0;
	while (i < N_CHUNK)
	{
		if (add_job(game, &game->link, &game->area[i], display_game))
			return (1);
		++i;
	}
	return (0);
}
