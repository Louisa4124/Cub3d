/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sprite_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:51:32 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/21 13:04:49 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	get_color_sprite(t_igs *igs, t_vec3d point)
{
	t_vec3d	u;
	t_vec3d	w;
	float	n;
	float	r;
	float	tmp_y;

	u = (t_vec3d){point.x - igs->pos.x, point.y - igs->pos.y, 0};
	w = (t_vec3d){igs->plan.b, -igs->plan.a, 0};
	n = 1 / sqrt((w.x * w.x) + (w.y * w.y));
	r = 0.5 + (u.x * w.x * n + u.y * w.y * n);
	if (r < 0 || r >= 1)
		return (-1);
	pthread_mutex_lock(&igs->m_ms);
	if (igs->ms >= 0.02)
	{
		igs->ms -= 0.02;
		igs->sp->y += igs->sp->ry;
		if (igs->sp->y >= igs->sp->ry * igs->sp->frame)
			igs->sp->y = 0;
	}
	tmp_y = igs->sp->y;
	pthread_mutex_unlock(&igs->m_ms);
	return (extract_pixel(igs->sp->img, r * igs->sp->img.width, \
		(1 - point.z - (int) point.z) * igs->sp->ry + tmp_y));
}

int	get_color_door(t_door *door, t_vec3d point)
{
	t_vec3d	u;
	t_vec3d	w;
	float	n;
	float	r;

	u = (t_vec3d){point.x - door->pos.x, point.y - door->pos.y, 0};
	w = (t_vec3d){door->plan.b, -door->plan.a, 0};
	n = 1 / sqrt((w.x * w.x) + (w.y * w.y));
	r = 0.5 + (u.x * w.x * n + u.y * w.y * n);
	if (r < 0 || r >= 1)
		return (-1);
	return (extract_pixel(*door->img, r * door->img->width, \
		(1 - point.z - (int) point.z) * door->img->width));
}
