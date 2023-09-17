/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:59:16 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/17 13:19:03 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// WIP

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define CHARSET "01"
#define START "NESW"

int	ft_randuint(int min, int max, int *err)
{
	unsigned int	c;
	int				fd;

	c = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		*err = 1;
	else
	{
		if (read(fd, &c, 1) == -1)
			*err = 1;
		close (fd);
	}
	return (c % (max + 1 - min) + min);
}

void	*ft_free2d(void **arr, int size)
{
	int	i;

	i = -1;
	if (!arr)
		return (NULL);
	if (!size)
	{
		while (arr[++i])
			arr[i] = ft_free_secure(arr[i]);
	}
	else
	{
		while (++i < size)
			arr[i] = ft_free_secure(arr[i]);
	}
	free(arr);
	return (NULL);
}

char	**allocate(int width, int height)
{
	char	**map;
	int		i;

	map = malloc((height + 1) * sizeof(void *));
	if (!map)
		return (NULL);
	map[height] = NULL;
	while (height-- > 0)
	{
		map[height] = malloc((width + 1) * sizeof(char));
		if (map[height] == NULL)
			return (ft_free2d((void **) map, 0));
		i = -1;
		while (++i < width)
			map[height][i] = ' ';
	}
	return (map);
}

void	fill_map_rec(char **map, int max[2], int x, int y)
{
	int	err;
	int	i;

	if (map[y][x] != ' ' || x >= max[0] || x <= 0 || y >= max[1] || y <= 0)
		return ;
	err = 0;
	i = ft_randuint(0, sizeof(CHARSET), &err);
	map[y][x] = CHARSET[i];
	fill_map_rec(map, max, x - 1, y);
	fill_map_rec(map, max, x + 1, y);
	fill_map_rec(map, max, x, y - 1);
	fill_map_rec(map, max, x, y + 1);
}


int	fill_map(char **map, int max[2])
{
	int	err;
	int	i;
	int	x;
	int	y;

	err = 0;
	y = ft_randuint(4, max[0] - 4, &err);
	x = ft_randuint(4, max[1] - 4, &err);
	if (err)
		return (1);
	i = ft_randuint(0, sizeof(CHARSET), &err);
	map[y][x] = CHARSET[i];
	fill_map_rec(map, max, x - 1, y);
	return (0);
}

int	generate(int width, int height)
{
	char	**map;
	int		max[2];

	if (width <= 10 || height <= 10)
		return (1);
	map = allocate(width, height);
	if (!map)
		return (1);
	max[0] = height;
	max[1] = width;
	if (fill_map(map, max))
		return (ft_free2d((void **) map, 0), 1);
}

int	main(int ac, char **arg)
{
	if (ac == 2)
		return (generate(atoi(arg[1]), atoi(arg[1])));
	else if (ac == 3)
		return (generate(atoi(arg[1]), atoi(arg[2])));
	return (dprintf(2, "Error\n"), 1);
}
