/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:36:25 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/03 14:46:20 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

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

void	ft_jobclear(t_list **lst, void (*del)(void *))
{
	t_list	*buff;

	if (!(*del) || !lst)
		return ;
	while (*lst)
	{
		buff = (*lst)->next;
		ft_lstdelone(*lst, (*del));
		*lst = buff;
	}
	lst = NULL;
}
