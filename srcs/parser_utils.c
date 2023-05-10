/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:49:15 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/10 13:50:27 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
