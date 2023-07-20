/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:49:15 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/19 16:13:37 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	only_space(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
	{
		if (line[i] == '\t')
			len += 4;
		else
			++len;
		++i;
	}
	if (line[i] == '\0')
		return (-1);
	return (i);
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

int	extract_map_error(t_list **lst, int **layout, int size, char *errstr)
{
	ft_lstclear(lst, free);
	if (size)
		layout = ft_free2d((void **)layout, size);
	else
		layout = ft_free_secure(layout);
	if (errstr)
		ft_putstr_fd(errstr, 2);
	return (1);
}
