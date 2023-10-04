/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:36:17 by tlegrand          #+#    #+#             */
/*   Updated: 2023/10/04 13:19:52 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_len_max(t_list *lst);
int	is_start(char c);

static int	extract_lst(t_list **lst, char *line)
{
	t_list	*new;
	int		i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		++i;
	if (line[i] == '\0' && *lst == NULL)
		return (free(line), 0);
	else if (line[i] == '\0')
		return (free(line), 1);
	new = ft_lstnew((void *) line);
	if (!new)
	{
		ft_lstclear(lst, free);
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (2);
	}
	ft_lstadd_back(lst, new);
	return (0);
}

static int	extract_map_get_start(t_game *game, char c, int x, int y)
{
	if (game->pos.z != -1)
		return (1);
	game->pos.x = x + 0.5;
	game->pos.y = y + 0.5;
	game->pos.z = 0.5;
	game->map.layout[y][x] = 0;
	if (c == 'N')
		game->angle_z = 0;
	else if (c == 'S')
		game->angle_z = PI;
	else if (c == 'W')
		game->angle_z = PI_3_QUARTER;
	else if (c == 'E')
		game->angle_z = PI_HALF;
	return (0);
}

static int	extract_map_line(t_map *map, t_game *game, char *line, int y)
{
	int	x;

	x = 0;
	while (line[x] && line[x] != '\n' && x < map->x_size)
	{
		if (line[x] == '0')
			map->layout[y][x] = 0;
		else if (line[x] == '1')
			map->layout[y][x] = 1;
		else if (line[x] == ' ')
			map->layout[y][x] = -1;
		else if (is_start(line[x]))
		{
			if (extract_map_get_start(game, line[x], x, y))
				return (ft_putstr_fd("Error\nToo much starting pos\n", 2), 1);
		}
		else
			return (ft_putstr_fd("Error\nUnexpected char in map\n", 2), 1);
		++x;
	}
	while (x < map->x_size)
		map->layout[y][x++] = -1;
	return (0);
}

static int	extract_map(t_map *map, t_game *game, t_list **lst)
{
	t_list	*current;
	int		y;

	map->y_size = ft_lstsize(*lst);
	if (map->y_size == 0)
		return (ft_putstr_fd("Error\nNo map\n", 2), 1);
	map->layout = ft_calloc(map->y_size, sizeof(void *));
	if (!map->layout)
		return (ft_putstr_fd("Error\nMalloc failed\n", 2), 1);
	map->x_size = ft_len_max(*lst);
	y = 0;
	current = *lst;
	while (y < map->y_size)
	{
		map->layout[y] = ft_calloc(map->x_size, sizeof(int));
		if (map->layout[y] == NULL)
			return (ft_putstr_fd("Error\nMalloc failed\n", 2), 1);
		if (extract_map_line(map, game, (char *)current->content, y))
			return (1);
		current = current->next;
		++y;
	}
	if (game->pos.z == -1)
		return (ft_putstr_fd("Error\nNo starting pos in map\n", 2), 1);
	return (0);
}

int	parser_map(t_map *map, t_game *game, int fd)
{
	char	*line;
	t_list	*lst;
	int		wit;

	wit = 0;
	lst = NULL;
	game->pos.z = -1;
	while (wit == 0)
	{
		if (get_next_line(fd, &line))
		{
			ft_lstclear(&lst, free);
			return (perror("Error\n"), 1);
		}
		if (line == NULL)
			break ;
		wit = extract_lst(&lst, line);
	}
	if (wit == 2)
		return (ft_free_secure(line), 1);
	wit = extract_map(map, game, &lst);
	ft_lstclear(&lst, free);
	return (wit);
}
