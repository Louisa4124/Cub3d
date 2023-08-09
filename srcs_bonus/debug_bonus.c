/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:33:34 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/09 12:33:31 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	debug_print_mlx(t_mlx *mlx)
{
	dprintf(2, "####	t_mlx	####\n");
	dprintf(2, "mlx->ptr : %p\n", mlx->ptr);
	dprintf(2, "mlx->win : %p\n", mlx->win);
	dprintf(2, "	----	\n");
}

void	debug_print_img(t_img *img)
{
	dprintf(2, "####	t_img	####\n");
	dprintf(2, "img->id : %p\n", img->id);
	dprintf(2, "img->addr : %p\n", img->addr);
	dprintf(2, "img->height: %d\n", img->height);
	dprintf(2, "img->width: %d\n", img->width);
	dprintf(2, "img->ll: %d\n", img->ll);
	dprintf(2, "img->bpp: %d\n", img->bpp);
	dprintf(2, "img->endian: %d\n", img->endian);
	dprintf(2, "	----	\n");
}

void	debug_print_texture(t_texture *texture)
{
	int	i;

	i = 0;
	dprintf(2, "####	t_texture	####\n");
	while (i < 4)
	{
		debug_print_img(&texture->wall[i]);
		++i;
	}
	dprintf(2, "t->color floor : %#X\n", texture->floor);
	dprintf(2, "t->color ceiling : %#X\n", texture->ceiling);
	dprintf(2, "	----	\n");
}

void	debug_print_map(t_map *map)
{
	int	i;
	int	j;

	dprintf(2, "####	t_map	####\n");
	dprintf(2, "map->y_size : %d\n", map->y_size);
	dprintf(2, "map->x_size : %d\n", map->x_size);
	i = -1;
	while (++i < map->y_size)
	{
		j = -1;
		while (++j < map->x_size)
			dprintf(2, "%3d", map->layout[i][j]);
		dprintf(2, "\n");
	}
	dprintf(2, "	----	\n");
}

void	debug_print_vec3d(t_vec3d *u, char *name)
{
	if (name)
		dprintf(2, "%s\n", name);
	dprintf(2, "u.x = % .3f\n", u->x);
	dprintf(2, "u.y = % .3f\n", u->y);
	dprintf(2, "u.z = % .3f\n", u->z);
}

void	debug_print_queue(t_job *job)
{
	while (job)
	{
		dprintf(2, "jid : %d\tdata addr %p\tdata area %p\tfunc addr %p\n", \
			job->jid, job->data, job->area, job->func);
		dprintf(2, "current addr : %p\nnext addr : %p\n", job, job->next);
		job = job->next;
	}
}

void	debug_print_igs(t_igs *igs)
{
	int	i;

	i = -1;
	while (++i < N_IGS)
	{
		dprintf(2, "sp %p\n", igs[i].sp);
		dprintf(2, "pos (%f, %f, %f)\n", igs[i].pos.x, igs[i].pos.y, igs[i].pos.z);
		dprintf(2, "plan (%f, %f, %f, %f)\n", igs[i].plan.a, igs[i].plan.b, \
			igs[i].plan.c, igs[i].plan.d);
		dprintf(2, "distance %f\n", igs[i].t);
		dprintf(2, "time %f\n", igs[i].ms);
	}
}
