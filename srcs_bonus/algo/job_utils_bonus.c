/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:36:25 by tlegrand          #+#    #+#             */
/*   Updated: 2023/10/04 13:29:31 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

t_job	*jobnew(int jid, void *data, void *area, \
	void (*func)(void *, void *))
{
	t_job	*new;

	new = ft_calloc(1, sizeof(t_job));
	if (!new)
		return (NULL);
	new->jid = jid;
	new->data = data;
	new->area = area;
	new->func = func;
	return (new);
}

t_job	*joblast(t_job *current)
{
	if (current)
	{
		while (current->next)
			current = current->next;
	}
	return (current);
}

void	jobadd_back(t_job **HEAD, t_job *new)
{
	if (!HEAD || !new)
		return ;
	if (!*HEAD)
		*HEAD = new;
	else
		joblast(*HEAD)->next = new;
}

int	add_job(t_game *game, void *data, void *area, \
	void (*func)(void *, void *))
{
	static int	jid = 100;
	t_job		*new;

	new = jobnew(jid, data, area, func);
	if (new == NULL)
		return (jid);
	jobadd_back(game->queue, new);
	if (jid == INT_MAX)
		jid = 100;
	else
		++jid;
	++game->n_job;
	return (0);
}

void	clear_job(t_job **job)
{
	t_job	*buff;

	if (!job)
		return ;
	while (*job)
	{
		buff = (*job)->next;
		free(*job);
		*job = buff;
	}
	job = NULL;
}
