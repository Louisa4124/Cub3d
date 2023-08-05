/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:35:31 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/04 14:28:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	parser_error(int errnum)
{
	if (errnum == 1)
		ft_putstr_fd("Error\nCub3D only take .cub map\n", 2);
	return (errnum);
}

static int	check_name(char *name)
{
	while (*name)
	{
		if (!ft_strncmp(name, ".cub", 5))
			return (0);
		++name;
	}
	return (1);
}

static int	check_tiles(t_map *map, int y, int x)
{
	if (map->layout[y - 1][x] == -1)
		return (1);
	if (map->layout[y + 1][x] == -1)
		return (1);
	if (map->layout[y][x + 1] == -1)
		return (1);
	if (map->layout[y][x + 1] == -1)
		return (1);
	return (0);
}

static int	check_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			if (map->layout[y][x] == 0)
			{
				if (y == 0 || x == 0 || y == map->y_size - 1 || \
					x == map->x_size - 1 || check_tiles(map, y, x))
				{
					ft_putstr_fd("Error\nMap not surrounded by wall\n", 2);
					return (1);
				}
			}
			++x;
		}
		++y;
	}
	return (0);
}

int	parser(char *pathname, t_game *game)
{
	int		fd;

	s_map_init(&game->map);
	s_texture_init(&game->texture);
	if (check_name(pathname))
		return (parser_error(1));
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), 1);
	if (parser_texture(&game->mlx, &game->texture, fd))
	{
		close(fd);
		return (2);
	}
	if (parser_map(&game->map, game, fd))
	{
		close(fd);
		return (3);
	}
	close(fd);
	if (check_map(&game->map))
		return (4);
	return (0);
}
