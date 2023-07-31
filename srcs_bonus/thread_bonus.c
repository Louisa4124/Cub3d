/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:31:42 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/31 15:32:02 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	thread_do(t_game *game, void *(f)(void *))
{
	int	i;

	i = -1;
	i = -1;
	while (++i < N_THREAD)
	{
		if (pthread_create(&game->pid[i], NULL, f, &game->th[i]))
			dprintf(2, " ER THR\n");
	}
	while (--i >= 0)
		pthread_join(game->pid[i], NULL);
	return (0);
}
