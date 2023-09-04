/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_igs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:45:57 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/04 14:47:05 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	update_igs_time(t_igs *igs)
{
	int	i;

	i = 0;
	while (i < N_IGS)
	{
		igs[i].ms += 0.0015;
		++i;
	}
}

void	update_igs_plane(t_igs *igs, t_vec3d player)
{
	t_igs	tmp[2 * N_IGS + 1];
	int		i;
	int		s;

	i = -1;
	s = N_IGS;
	while (++i < N_IGS)
	{
		igs[i].plan.a = igs[i].pos.x - player.x;
		igs[i].plan.b = igs[i].pos.y - player.y;
		igs[i].plan.d = -igs[i].plan.a * igs[i].pos.x \
			- igs[i].plan.b * igs[i].pos.y;
		igs[i].t = sqrt(igs[i].plan.a * igs[i].plan.a \
			+ igs[i].plan.b * igs[i].plan.b);
		if (i == 0)
			tmp[s] = igs[i];
		else if (igs[i].t < tmp[s].t)
		{
			--s;
			tmp[s] = igs[i];
		}
		else
			tmp[s + i] = igs[i];
	}
	i = -1;
	while (++i < N_IGS)
		igs[i] = tmp[i + s];
	// dprintf(2, "START\n");
	// debug_print_igs(igs);
	// dprintf(2, "END\n");
}
