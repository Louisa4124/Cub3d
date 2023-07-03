/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:49:15 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/03 21:24:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	ft_len_max(t_list *lst)
{
	int	max;
	int	tmp;

	max = 0;
	while (lst)
	{
		tmp = ft_strlen2((char *)lst->content);
		if (tmp > max)
			max = tmp;
		lst = lst->next;
	}
	return (max);
}

int	extract_map_line_tab(t_map *map, int y, int x)
{
	map->layout[y][x] = -1;
	map->layout[y][x + 1] = -1;
	map->layout[y][x + 2] = -1;
	map->layout[y][x + 3] = -1;
	return (4);
}

int	extract_map_error(t_list **lst, int **layout, int size, char *errstr)
{
	ft_lstclear(lst, free);
	if (size)
		ft_free2d((void **)layout, size);
	else
		free(layout);
	ft_putstr_fd(errstr, 2);
	return (1);
}
