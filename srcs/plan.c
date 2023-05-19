/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/05/19 14:58:58 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
