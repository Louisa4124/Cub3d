/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:57:36 by lboudjem          #+#    #+#             */
/*   Updated: 2023/05/15 17:34:49 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_creat_plan_h(t_game *game)
{
	int	i;

	i = 0;
	while (i <= HEIGHT)
	{
		//dprintf(2, "i = %d\n", i);
		game->plan[0][i].a = 0;
		game->plan[0][i].b = 1;
		game->plan[0][i].c = 0;
		game->plan[0][i].d = -i;
		i++;
	}
}

void	ft_creat_plan_v(t_game *game)
{
	int	i;

	i = 0;
	while (i <= WIDTH)
	{
       // dprintf(2, "j = %d\n", i);
		game->plan[1][i].a = 1;
		game->plan[1][i].b = 0;
		game->plan[1][i].c = 0;
		game->plan[1][i].d = -i;
		i++;
	}
}
