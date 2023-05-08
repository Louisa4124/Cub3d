/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:00 by lboudjem          #+#    #+#             */
/*   Updated: 2023/05/08 15:58:06 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_inter_plan_line(t_game *game, t_plan *plan, t_vec3d *ray)
{
	t_vec3d	inter;
	float	t;

	t = -(plan->a * game->camera.x + plan->b * game->camera.y + plan->c * \
		game->camera.z + plan->d);
	inter.x = game->camera.x;
}

static inline short int	in_map(t_map *map, int x, int y)
{
	return (x >= 0 && x < map->w && y >= 0 && y < map->h \
			&& map->map[y][x] == 1);
}

float	intersec_planes_e(t_param *p, t_line line, float *r_w, float *r_h)
{
	int			i;
	t_vec		result;
	float		t;

	i = p->map->player.x;
	if (p->map->player.x < 0)
		i = -1;
	while (++i <= p->map->w)
	{
		if (p->map->p_e[i] && inter_line_plane_x(line, -i, &result, &t) \
				&& t > 0 && result.y >= 0)
		{
			if (result.z >= 0 && result.z < 1)
			{
				*r_w = result.y - (int)result.y;
				*r_h = 1 - result.z;
				if (in_map(p->map, i, result.y))
					return (t);
			}
			else if (p->map->player.z >= 0 && p->map->player.z < 1)
				return (-1);
		}
	}
	return (-1);
}

float	intersec_planes_w(t_param *p, t_line line, float *r_w, float *r_h)
{
	int			i;
	t_vec		result;
	float		t;

	i = p->map->player.x + 1;
	if (i > p->map->w + 1)
		i = p->map->w + 1;
	while (i-- >= 0)
	{
		if (p->map->p_w[i] && inter_line_plane_x(line, -i, &result, &t) \
				&& t > 0 && result.y >= 0)
		{
			if (result.z >= 0 && result.z < 1)
			{
				*r_w = 1 - result.y + (int)result.y;
				*r_h = 1 - result.z;
				if (in_map(p->map, i - 1, result.y))
					return (t);
			}
			else if (p->map->player.z >= 0 && p->map->player.z < 1)
				return (-1);
		}
	}
	return (-1);
}

float	intersec_planes_s(t_param *p, t_line line, float *r_w, float *r_h)
{
	int			i;
	t_vec		result;
	float		t;

	i = p->map->player.y;
	if (p->map->player.y < 0)
		i = -1;
	while (++i <= p->map->h)
	{
		if (p->map->p_s[i] && inter_line_plane_y(line, -i, &result, &t) \
				&& t > 0 && result.x >= 0)
		{
			if (result.z >= 0 && result.z < 1)
			{
				*r_w = 1 - result.x + (int)result.x;
				*r_h = 1 - result.z;
				if (in_map(p->map, result.x, i))
					return (t);
			}
			else if (p->map->player.z >= 0 && p->map->player.z < 1)
				return (-1);
		}
	}
	return (-1);
}

float	intersec_planes_n(t_param *p, t_line line, float *r_w, float *r_h)
{
	int			i;
	t_vec		result;
	float		t;

	i = p->map->player.y + 1;
	if (i > p->map->h + 1)
		i = p->map->h + 1;
	while (i-- >= 0)
	{
		if (p->map->p_n[i] && inter_line_plane_y(line, -i, &result, &t) \
				&& t > 0 && result.x >= 0)
		{
			if (result.z >= 0 && result.z < 1)
			{
				*r_w = result.x - (int)result.x;
				*r_h = 1 - result.z;
				if (in_map(p->map, result.x, i - 1))
					return (t);
			}
			else if (p->map->player.z >= 0 && p->map->player.z < 1)
				return (-1);
		}
	}
	return (-1);
}