/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/05/08 14:39:40 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_creat_plan_h(t_game *game)
{
	int	i;

	i = 0;
	while (i < height - 1)
	{
		game->plan_h[i].a = 0;
		game->plan_h[i].b = 1;
		game->plan_h[i].c = 0;
		game->plan_h[i].d = -i;
		i++;
	}
}

void	ft_creat_plan_v(t_game *game)
{
	int	i;

	i = 0;
	while (i < width - 1)
	{
		game->plan_v[i].a = 1;
		game->plan_v[i].b = 0;
		game->plan_v[i].c = 0;
		game->plan_v[i].d = -i;
		i++;
	}
}
