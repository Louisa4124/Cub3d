/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:49:15 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/05 21:24:36 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_start(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_line_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line && line[i])
	{
		if (line[i] == '\t')
			len += 4;
		else
			++len;
		++i;
	}
	return (len);
}

int	ft_len_max(t_list *lst)
{
	int	max;
	int	tmp;

	max = 0;
	while (lst)
	{
		tmp = ft_line_len((char *)lst->content);
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
