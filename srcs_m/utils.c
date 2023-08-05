/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:17:36 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/05 19:51:46 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float	pi_modulo(float z)
{
	if (z >= PI_DOUBLE)
		z -= PI_DOUBLE;
	else if (z <= -PI_DOUBLE)
		z += PI_DOUBLE;
	return (z);
}

void	view_update_dir(t_game *game)
{
	if (game->bit_key & BFLAG_RIGHT)
		game->angle_z += ANG_OFFSET_KEY;
	if (game->bit_key & BFLAG_LEFT)
		game->angle_z -= ANG_OFFSET_KEY;
	game->angle_z = pi_modulo(game->angle_z);
}

int	math_sign_float(float f)
{
	if (f < 0)
		return (-1);
	else if (f > 0)
		return (1);
	return (0);
}
