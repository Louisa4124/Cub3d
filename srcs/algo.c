/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/06/20 16:03:04 by tlegrand         ###   ########.fr       */
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
	return (*(unsigned int *)(game->texture.wall[wall].addr + \
		y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8)));
}

int	ft_print_texture_so_ea(t_game *game, int wall)
{
	int	x;
	int	y;

	x = 0;
	y = 0;

	x = (int)(((game->pos.y + game->point.y) - (int)(game->pos.y + \
		 game->point.y)) * game->texture.wall[1].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - \
		(int)(game->point.z)) * game->texture.wall[wall].height) - 1;
		return (*(unsigned int *)(game->texture.wall[wall].addr + \
		y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8)));
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
		return (ft_print_texture_no_we(game, 0));
	else if (game->u_plan.x == 1 && (game->pos.x + game->point.x) < game->pos.x 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.x_size 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 
		&& game->map.layout[(int)(game->pos.y + game->point.y)][(int)\
		(-game->plan[game->u_plan.x][game->u_plan.y].d - 1)] == 1)
		return (ft_print_texture_so_ea(game, 1));
	else if (game->u_plan.x == 0 && (game->pos.y + game->point.y) > game->pos.y \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) < game->map.y_size \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) >= 0 
		&& game->map.layout[(int)(-game->plan[game->u_plan.x][game->u_plan.y].d)] \
		[(int)(game->pos.x + game->point.x)] == 1)
		return (ft_print_texture_no_we(game, 2));
	else
		return (ft_print_texture_so_ea(game, 0));
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

int ft_update_rays(t_game *game, int u, int v, int wit)
{
	game->t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * \
		game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / game->t;
	if (wit == 0 && game->t > game->close_t)
		return (1);
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
	else if (game->t <= 0)
		return (game->texture.floor);
}



// plan = 0 -> y
// plan = 1 -> x
// i -> y         j -> x
int	ft_intersect(t_game *game, int pos, int max, int plan, int found, int dir)
{
	int	wit;

	wit = 1;
	while (pos >= 0 && pos <= max && wit > 0 && dir != 0)
	{
		game->t = (game->plan[plan][pos].a * game->u_rays.x + game->plan[plan][pos].b \
				* game->u_rays.y + game->plan[plan][pos].c * game->u_rays.z);
		if (game->t != 0)
			wit = ft_update_rays(game, pos, plan, found);
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
// add && U > 0
int	intersect_2(t_game *game, int max, int plan, int *pos, int found, int dir)
{
	int	wit;
	int	i;

	wit = 1;
	i = 0;
	while (i < max && wit > 0)
	{
		game->t = (game->plan[plan][*pos].a * game->u_rays.x + game->plan[plan][*pos].b \
				* game->u_rays.y + game->plan[plan][*pos].c * game->u_rays.z);
		if (game->t != 0)
			wit = ft_update_rays(game, *pos, plan, found);
		*pos += dir;
		if (*pos < 0)
			return (1);
		if (plan == 1 && *pos > game->map.x_size)
			return (1);
		if (plan == 0 && *pos > game->map.y_size)
			return (1);
		++i;
	}
	return (wit);
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

int	ft_intersectest(t_game *game, int *pos, int max, int plan, int found, int dir)
{
	int	wit;
	int	i;

	wit = 1;
	i = 0;
	if (dir == 0)
		return (wit);
	while (wit > 0 && *pos >= 0 && *pos <= max)
	{
		game->t = (game->plan[plan][*pos].a * game->u_rays.x + game->plan[plan][*pos].b \
				* game->u_rays.y + game->plan[plan][*pos].c * game->u_rays.z);
		if (game->t != 0)
			wit = ft_update_rays(game, *pos, plan, found);
		*pos += dir;
	}
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
	int		i = 0;

	k = ft_give_me_ratio(game->u_rays.x, game->u_rays.y);
	pos_x = game->pos.x;
	pos_y = game->pos.y;
	dir_x = ft_sign_comp(game->u_rays.x);
	dir_y = ft_sign_comp(game->u_rays.y);
	wit_x = 1;
	wit_y = 1;
	while (wit_x > 0 && wit_y > 0)
	{
		// wit_x = intersect_2(game, 1, 1, &pos_x, wit_y, dir_x);
		// dprintf(2, "wit is %d\txpos is %d\n", wit_x, pos_x);
		// wit_y = intersect_2(game, 1, 0, &pos_y, wit_x, dir_y);
		wit_y = ft_intersectest(game, &pos_y, game->map.y_size, 0, wit_x, dir_y);
		wit_x = ft_intersectest(game, &pos_x, game->map.x_size, 1, wit_y, dir_x);
		// if (k > 0)
		// {
		// 	wit_x = intersect_2(game, 1, 1, &pos_x, 0, dir_x);
		// 	wit_y = intersect_2(game, k, 0, &pos_y, wit_x, dir_y);
		// }
		// else if (k < 0)
		// {
		// 	wit_y = intersect_2(game, 1, 0, &pos_y, 0, dir_y);
		// 	wit_x = intersect_2(game, -k, 1, &pos_x, wit_y, dir_x);
		// }
		// else
		// {
		// 	wit_x = intersect_2(game, 1, 1, &pos_x, 0, dir_x);
		// 	wit_y = intersect_2(game, 1, 0, &pos_y, wit_x, dir_y);
		// }
		// if (i)
		// 	dprintf(2, "count %d\n", i);
		// ++i;
	}
	// dprintf(2, "OUT\n");
	if (wit_y == 0 || wit_x == 0)
		return (ft_print_texture(game));
	else
		return (ft_print_ceiling_floor(game));
}

int	ft_update_game(t_game *game)
{
	int		i;
	int		j;
	int		color;
	t_vec3d	ray_tmp;

	i = 0;
	ft_move(game);
	tourn(game);
	while (i < game->mlx.win_height)
	{
		j = 0;
		while (j < game->mlx.win_width)
		{
			
			ray_tmp.x = game->rays[i][j].x;
			ray_tmp.y = game->rays[i][j].y * cos(game->angle_x) + game->rays[i][j].z * -sin(game->angle_x);
			ray_tmp.z= game->rays[i][j].y * sin(game->angle_x) + game->rays[i][j].z * cos(game->angle_x);
			game->u_rays.x = ray_tmp.x * cos(game->angle_z) + game->rays[i][j].y * -sin(game->angle_z);
			game->u_rays.y = ray_tmp.x * sin(game->angle_z) + game->rays[i][j].y * cos(game->angle_z);
			game->u_rays.z = ray_tmp.z;
			game->close_t = 0;
			color = ft_algo_the_third(game);
			ft_resolution(game, i, j, color);
			j += RESOLUTION;
			// dprintf(2, "END RAYS\n");
		}
		i += RESOLUTION;
	}
	// dprintf(2, "END FRAME\n");
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	ft_printf_fps();
	return (0);
}

// plan du sol : {0, 0, 1, 0}
// plan du plafond : {0, 0, 1, -1}

