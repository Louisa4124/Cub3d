/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/05/22 20:06:52 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	ft_create_plan_range_size(int *plan, int size)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (i < size)
	{
		if (plan[i] == 1)
		{
			++len;
			while (i < size && plan[i] == 1)
				++i;
		}
		++i;
	}
	return (len);
}

static int	*ft_create_plan_range(t_map *map, int y)
{
	int	*range;
	int	len;
	int	i;
	int	j;

	len = ft_create_plan_range_size(map->layout[y], map->x_size);
	range = ft_calloc(2 * len + 1, sizeof(int));
	if (!range)
		return (NULL);
	i = 0;
	j = 0;
	while (i < map->x_size)
	{
		if (map->layout[y][i] == 1)
		{
			range[j++] = i;
			while (i < map->x_size && map->layout[y][i] == 1)
				++i;
			range[j++] = i - 1;
		}
		++i;
	}
	return (range);
}

static int	ft_create_plan_range_v_size(int **plan, int x, int size)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (i < size)
	{
		if (plan[i][x] == 1)
		{
			++len;
			while (i < size && plan[i][x] == 1)
				++i;
		}
		++i;
	}
	return (len);
}

static int	*ft_create_plan_range_v(t_map *map, int x)
{
	int	*range;
	int	len;
	int	i;
	int	j;

	len = ft_create_plan_range_v_size(map->layout, x, map->y_size);
	range = ft_calloc(2 * len + 1, sizeof(int));
	if (!range)
		return (NULL);
	i = 0;
	j = 0;
	while (i < map->y_size)
	{
		if (map->layout[i][x] == 1)
		{
			range[j++] = i;
			while (i < map->y_size && map->layout[i][x] == 1)
				++i;
			range[j++] = i - 1;
		}
		++i;
	}
	return (range);
}
	// i = 0;
	// dprintf(2, "plan %d : ", y);
	// dprintf(2, "%d ", range[i++]);
	// dprintf(2, "%d ", range[i]);
	// while (range[++i])
	// 	dprintf(2, "%d ", range[i]);
	// dprintf(2, "\n");

int	ft_creat_plan_h(t_game *game)
{
	int	i;

	i = 0;
	game->plan[0] = malloc(sizeof(t_plan) * (game->map.y_size + 1));
	if (!game->plan[0])
		return (0);
	while (i < game->map.y_size)
	{
		game->plan[0][i].a = 0;
		game->plan[0][i].b = 1;
		game->plan[0][i].c = 0;
		game->plan[0][i].d = -i;
		game->plan[0][i].range = ft_create_plan_range(&game->map, i);
		i++;
	}
	return (1);
}

int	ft_creat_plan_v(t_game *game)
{
	int	i;

	i = 0;
	game->plan[1] = malloc(sizeof(t_plan) * (game->map.x_size + 1));
	if (!game->plan[1])
		return (0);
	while (i < game->map.x_size)
	{
		game->plan[1][i].a = 1;
		game->plan[1][i].b = 0;
		game->plan[1][i].c = 0;
		game->plan[1][i].d = -i;
		game->plan[1][i].range = ft_create_plan_range_v(&game->map, i);
		i++;
	}
	return (1);
}

int	ft_creat_plans(t_game *game)
{
	game->plan = malloc (sizeof(t_plan *) * 2);
	if (!game->plan)
		return (0);
	if (!ft_creat_plan_h(game))
		return (0);
	if (!ft_creat_plan_v(game))
		return (0);
	return (1);
}

int	belong_in_ranges(int p, int *range)
{
	int	i;

	i = 0;
	if (p >= range[i] && p <= range[++i])
		return (1);
	while (range[++i])
	{
		if (p >= range[i] && p <= range[++i])
			return (1);
	}
	return (0);
}
