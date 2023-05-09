/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:36:17 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/09 16:41:51 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	extract_lst(t_list **lst, char *line)
{
	t_list	*new;
	int		i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		++i;
	if (line[i] == '\0' && *lst == NULL)
		return (0);
	else if (line[i] == '\0')
		return (1);
	new = ft_lstnew((void *) line);
	if (!new)
	{
		ft_lstclear(lst, free);
		ft_putstr_fd("Error : malloc failed\n", 2);
		return (2);
	}
	ft_lstadd_back(lst, new);
	return (0);
}

static int	ft_len_max(t_list *lst)
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

static int	map_get_int(char c)
{
	if (c == ' ')
		return (-1);
	if (c == '1' || c == '0')
		return (c - 48);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (-2);
}

static int	extract_map(t_map *map, t_vec3d *pos, t_vec3d *dir, t_list **lst)
{
	int	x;
	int	y;

	map->y_size = ft_lstsize(*lst);
	map->layout = ft_calloc(map->y_size, sizeof(void *));
	if (!map->layout)
	{
		ft_lstclear(lst, free);
		ft_putstr_fd("Error : malloc failed\n", 2);
		return (1);
	}
	map->x_size = ft_len_max(*lst);
	y = 0;
	while (y++ < map->x_size)
	{
		x = 0;
		map->layout[y] = ft_calloc(map->x_size, sizeof(int));
		while (((char *)(*lst)->content)[x])
		{
			map->layout[y][x] = map_get_int(((char *)(*lst)->content)[x]);
			++x;
		}
	}
}

int	parser_map(t_map *map, t_vec3d *pos, t_vec3d *dir, int fd)
{
	char	*line;
	t_list	*lst;
	int		wit;

	wit = 0;
	lst = NULL;
	while (wit == 0)
	{
		if (get_next_line(fd, &line))
		{
			ft_lstclear(&lst, free);
			return (perror("Error : "), 1);
		}
		if (line == NULL)
			break ;
		wit = extract_lst(&lst, line);
	}
	if (wit == 2)
		return (1);
	if (extract_map(map, pos, dir, &lst))
		return (1);
	ft_lstclear(&lst, free);
	return (0);
}
