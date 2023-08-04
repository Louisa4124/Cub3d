/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:36:25 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/03 21:17:20 by tlegrand         ###   ########.fr       */
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

int	add_job(t_job **head, void *data, void *area, \
	void (*func)(void *, void *))
{
	static int	jid;
	t_job		*new;

	new = jobnew(jid, data, area, func);
	if (new == NULL)
		return (1 + jid);
	jobadd_back(head, new);
	if (jid == INT_MAX)
		jid = 0;
	else
		++jid;
	return (0);
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
