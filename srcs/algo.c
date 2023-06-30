/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/06/30 13:27:00 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int64_t	g_fps;
int		g_frame;

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

void	tourn(t_game *game)
{
	int	x_quarter;
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	x_quarter = game->mlx.win_width >> 2;
	if (x >=0 && x < x_quarter)
	{
		game->angle_z -= 0.07;
		game->dir = ft_rotate_vec_z(game->dir, -0.007);
	}
	else if (x > x_quarter * 3 && x <= game->mlx.win_width)
	{
		game->angle_z += 0.07;
		game->dir = ft_rotate_vec_z(game->dir, 0.007);
	}
	if (game->angle_z >= PI * 2)
		game->angle_z -= PI * 2;
	else if (game->angle_z <= -PI * 2)
		game->angle_z += PI * 2;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *) img->addr + (y * img->ll + x * (img->bpp >> 3));
	*(unsigned int *) dst = color;
}

int	ft_print_texture_no_we(t_game *game, int wall)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	x = (int)(((game->pos.x + game->point.x) - (int)(game->pos.x + \
		 game->point.x)) * game->texture.wall[wall].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - \
		(int)(game->point.z)) * game->texture.wall[wall].height) - 1;
	// dprintf(2, "in print : x is %d y is %d\n", x, y);
	return (*(unsigned int *)(game->texture.wall[wall].addr + \
		y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8)));
}
// protection offerflow
int	ft_print_texture_so_ea(t_game *game, int wall)
{
	int	x;
	int	y;
	int	ret;

	x = 0;
	y = 0;

	x = (int)(((game->pos.y + game->point.y) - (int)(game->pos.y + \
		 game->point.y)) * game->texture.wall[wall].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - \
		(int)(game->point.z)) * game->texture.wall[wall].height) - 1;
	// dprintf(2, " addr in uint : %lu\n", game->texture.wall[wall].addr);
	// return (ret);
	ret = *(unsigned int *)(game->texture.wall[wall].addr + \
		y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8));
	// if (ret > game->texture.wall[wall].height * game->texture.wall[wall].width || ret < 0)
	// {
	// 	dprintf(2, "color overflow ind wall %d\n", wall);
	// 	ret = RED;
	// }
	return (ret);
}

int	ft_print_texture_wall(t_game *game, int wall)
{
	int	x;
	int	y;
	int	ret;

	if (wall % 2 == 1)
		x = (int)(((game->pos.y + game->point.y) - (int)(game->pos.y + \
		 game->point.y)) * game->texture.wall[wall].width);
	else
		x = (int)(((game->pos.x + game->point.x) - (int)(game->pos.x + \
		 game->point.x)) * game->texture.wall[wall].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - \
		(int)(game->point.z)) * game->texture.wall[wall].height) - 1;
	ret = *(unsigned int *)(game->texture.wall[wall].addr + \
		y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8));
	// if (ret > game->texture.wall[wall].height * game->texture.wall[wall].width || ret < 0)
	// {
	// 	dprintf(2, "color overflow ind wall %d\n", wall);
	// 	ret = RED;
	// }
	return (ret);
}

int	ft_print_texture(t_game *game)
{
	game->point.x = game->u_rays.x * game->close_t;
	game->point.y = game->u_rays.y * game->close_t;
	game->point.z = 0.5 + game->u_rays.z * game->close_t;
	if (game->u_plan.x == 0 && (game->pos.y + game->point.y) < game->pos.y 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.y_size 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 
		&& game->map.layout[(int)(-game->plan[game->u_plan.x] \
		[game->u_plan.y].d - 1)][(int)(game->pos.x + game->point.x)] == 1)	
		return (ft_print_texture_wall(game, 0));
	else if (game->u_plan.x == 1 && (game->pos.x + game->point.x) < game->pos.x 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.x_size 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 
		&& game->map.layout[(int)(game->pos.y + game->point.y)][(int)\
		(-game->plan[game->u_plan.x][game->u_plan.y].d - 1)] == 1)
		return (ft_print_texture_wall(game, 1));
	else if (game->u_plan.x == 0 && (game->pos.y + game->point.y) > game->pos.y \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) < game->map.y_size \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) >= 0 
		&& game->map.layout[(int)(-game->plan[game->u_plan.x][game->u_plan.y].d)] \
		[(int)(game->pos.x + game->point.x)] == 1)
		return (ft_print_texture_wall(game, 2));
	else
		return (ft_print_texture_wall(game, 3));
}

int	ft_is_wall(t_game *game, int **layout, int u, int v)
{
	int d;
	int sumx;
	int sumy;
	
	d = -game->plan[v][u].d;
	sumx = game->pos.x + game->point.x;
	sumy = game->pos.y + game->point.y;
	if ((game->close_t == 0 
		|| game->t < game->close_t) && ((v == 0 
		&& sumy < game->pos.y && d < game->map.y_size 
		&& (d - 1) >= 0 && layout[d - 1][sumx] == 1) 
		|| (v == 1 && sumx < game->pos.x && (d - 1) < game->map.x_size 
		&& (d - 1) >= 0 && layout[sumy][d - 1] == 1)
		|| (v == 0 && sumy > game->pos.y && d < game->map.y_size 
		&& d >= 0 && layout[d][sumx] == 1)
		|| (v == 1 && sumx > game->pos.x&& d < game->map.x_size 
		&& d >= 0 && layout[sumy][d] == 1)))
		return (1);
	return (0);
}

int ft_update_rays(t_game *game, t_plan *plan, int u, int v, int wit)
{
	game->t = -(plan->a * game->pos.x + plan->b * \
		game->pos.y + plan->c * 0.5 + plan->d) / game->t;
	if (wit == 0 && game->t > game->close_t)
		return (-1);
	if (game->t > 0)
	{
		game->point.x = game->u_rays.x * game->t;
		game->point.y = game->u_rays.y * game->t;
		game->point.z = 0.5 + game->u_rays.z * game->t;
		if (game->point.z < 1 && game->point.z > 0
			&& (int)(game->pos.x + game->point.x) >= 0 
			&& (int)(game->pos.y + game->point.y) >= 0 
			&& (int)(game->pos.x + game->point.x) < game->map.x_size 
			&& (int)(game->pos.y + game->point.y) < game->map.y_size)
		{
			if (ft_is_wall(game, game->map.layout, u, v))
			{
				game->close_t = game->t;
				game->u_plan.x = v;
				game->u_plan.y = u;
				return (0);
			}
		}
		else
			return (-1);
	}
	return (1);
}

int	ft_print_ceiling_floor(t_game *game)
{
	game->t = (game->sky.a * game->u_rays.x + game->sky.b * game->u_rays.y \
		 + game->sky.c * game->u_rays.z);
	if (game->t > 0)
		return (game->texture.ceiling);
	else
		return (game->texture.floor);
}

// plan = 0 -> y
// plan = 1 -> x
// i -> y         j -> x
int	ft_intersect(t_game *game, int pos, int max, int id_plan, int found, int dir)
{
	int		wit;
	t_plan	*plan;

	wit = 1;
	plan = game->plan[id_plan];
	while (pos >= 0 && pos <= max && wit > 0 && dir != 0)
	{
		game->t = (plan[pos].a * game->u_rays.x + plan[pos].b \
				* game->u_rays.y + plan[pos].c * game->u_rays.z);
		if (game->t != 0)
			wit = ft_update_rays(game, &plan[pos], pos, id_plan, found);
		pos += dir;
	}
	return (wit);
}

int	ft_sign_comp(float f)
{
	if (f < 0)
		return (-1);
	else if (f > 0)
		return (1);
	return (0);
}

int	ft_switch_plan(t_game *game)
{
	int	wit_y;
	int	wit_x;

	wit_y = ft_intersect(game, game->pos.y, game->map.y_size, 0, 1, ft_sign_comp(game->u_rays.y));
	wit_x = ft_intersect(game, game->pos.x, game->map.x_size, 1, wit_y, ft_sign_comp(game->u_rays.x));
	
	if (wit_y == 0 || wit_x == 0)
		return (ft_print_texture(game));
	else
		return (ft_print_ceiling_floor(game));
}

void	ft_printf_fps(void)
{
	if (get_time() - g_fps < 1000)
		g_frame++;
	else
	{
		ft_printf("%d\n", g_frame);
		g_fps = get_time();
		g_frame = 0;
	}
}

void	ft_resolution(t_game *game, int i, int j, int color)
{
	int x;
	int	y;
	int	j2;

	x = i + RESOLUTION;
	y = j + RESOLUTION;
	j2 = j;
	while (i < x && i < game->mlx.win_height)
	{
		j = j2;
		while (j < y && j < game->mlx.win_width)
		{
			my_mlx_pixel_put(&game->view, j, i, color);
			++j;
		}
		++i;
	}
}

// rx ratio de x pour 1y
// ry ratio de y pour 1x  
// return k > 0 for rx 
// return k < 0 for ry
int	ft_give_me_ratio(float x, float y)
{
	float	r_x;
	float	r_y;
	int		kx;
	int		ky;

	r_x = x / y;
	r_y = y / x;
	kx = r_x;
	ky = r_y;
	if (kx)
		return (ft_abs(kx));
	else if (ky)
		return (-ft_abs(ky));
	return (0);
}

int	ft_intersectest(t_game *game, int *pos, int max, int plan, int *found, int dir, int limit)
{
	int	wit;
	int	i;

	wit = 1;
	i = 0;
	if (dir == 0)
		return (-1);
	while (wit > 0 && *pos >= 0 && *pos <= limit && i < max)
	{
		game->t = (game->plan[plan][*pos].a * game->u_rays.x + game->plan[plan][*pos].b \
				* game->u_rays.y + game->plan[plan][*pos].c * game->u_rays.z);
		if (game->t != 0)
			wit = ft_update_rays(game, &game->plan[plan][*pos], *pos, plan, *found);
		*pos += dir;
		++i;
	}
	if (*pos < 0 || *pos > limit)
		return (-1);
	if (wit == 0)
		*found = 0;
	return (wit);
}

int	ft_algo_the_third(t_game *game)
{
	t_vec3d	tmp_ray;
	int		k;
	int		pos_x;
	int		pos_y;
	int		wit_y;
	int		wit_x;
	int		dir_x;
	int		dir_y;
	int		found;
	int		i = 0;

	k = ft_give_me_ratio(game->u_rays.x, game->u_rays.y);
	pos_x = game->pos.x;
	pos_y = game->pos.y;
	dir_x = ft_sign_comp(game->u_rays.x);
	dir_y = ft_sign_comp(game->u_rays.y);
	wit_x = 1;
	wit_y = 1;
	found = 1;
	while (wit_x > 0 || wit_y > 0)
	{
		if (k > 0)
		{
			if (wit_x > 0)
				wit_x = ft_intersectest(game, &pos_x, 1, 1, &found, dir_x, game->map.x_size);
			if (wit_y > 0)
				wit_y = ft_intersectest(game, &pos_y, k, 0, &found, dir_y, game->map.y_size);
		}
		else if (k < 0)
		{
			if (wit_y > 0)
				wit_y = ft_intersectest(game, &pos_y, 1, 0, &found, dir_y, game->map.y_size);
			if (wit_x > 0)
				wit_x = ft_intersectest(game, &pos_x, -k, 1, &found, dir_x, game->map.x_size);
		}
		else
		{
			if (wit_x > 0)
				wit_x = ft_intersectest(game, &pos_x, 1, 1, &found, dir_x, game->map.x_size);
			if (wit_y > 0)
				wit_y = ft_intersectest(game, &pos_y, 1, 0, &found, dir_y, game->map.y_size);
		}
	}
	if (found == 0)
		return (ft_print_texture(game));
	else
		return (ft_print_ceiling_floor(game));
}


int	ft_update_game(t_game *game)
{
	int		i;
	int		j;
	int		color;
	int		size;
	t_vec3d	ray_tmp;

	i = 0;
	size = 10;
	ft_move(game);
	tourn(game);
	while (i < game->mlx.win_height && game->fps_booster == 0 && game->pause == 0)
	{
		j = 0;
		while (j < game->mlx.win_width && game->fps_booster == 0 && game->pause == 0)
		{
			
			if (i > 10 && i < (game->map.y_size * size) + 10 && j > 10 && j < (game->map.x_size * size) + 10)
			{
				j += RESOLUTION;
				continue ;
			}
			ray_tmp = ft_rotate_vec_x(game->rays[i][j], game->angle_x);
			game->u_rays = ft_rotate_vec_z(ray_tmp, game->angle_z);
			game->close_t = 0;
			color = ft_switch_plan(game);
			ft_resolution(game, i, j, color);
			j += RESOLUTION;
		}
		i += RESOLUTION;
	}
	if (game->fps_booster == 0 && game->pause == 0)
		drawMap2D(game, size);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	ft_printf_fps();
	//printf("pause = %d\n", game->pause);
	return (0);
}

// plan du sol : {0, 0, 1, 0}
// plan du plafond : {0, 0, 1, -1}
// rays entre -1.000 et 1.000
// NO -> 0
// SO -> 1
// WE -> 2
// EA -> 3