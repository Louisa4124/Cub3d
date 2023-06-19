/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/06/19 14:48:32 by lboudjem         ###   ########.fr       */
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

void	ft_print_texture_no_we(t_game *game, int wall, int i, int j)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	x = (int)(((game->pos.x + game->point.x) - (int)(game->pos.x + \
		 game->point.x)) * game->texture.wall[wall].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - \
		(int)(game->point.z)) * game->texture.wall[wall].height) - 1;
	game->color = *(unsigned int *)(game->texture.wall[wall].addr + \
		y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8));
}

void	ft_print_texture_so_ea(t_game *game, int wall, int i, int j)
{
	int	x;
	int	y;

	x = 0;
	y = 0;

	x = (int)(((game->pos.y + game->point.y) - (int)(game->pos.y + \
		 game->point.y)) * game->texture.wall[1].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - \
		(int)(game->point.z)) * game->texture.wall[wall].height) - 1;
	game->color = *(unsigned int *)(game->texture.wall[wall].addr + \
		y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8)); //dark	
}

void	ft_print_texture(t_game *game, int i, int j)
{
	game->point.x = game->u_rays.x * game->close_t;
	game->point.y = game->u_rays.y * game->close_t;
	game->point.z = 0.5 + game->u_rays.z * game->close_t;
	if (game->u_plan.x == 0 && (game->pos.y + game->point.y) < game->pos.y 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.y_size 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 
		&& game->map.layout[(int)(-game->plan[game->u_plan.x] \
		[game->u_plan.y].d - 1)][(int)(game->pos.x + game->point.x)] == 1)	
		ft_print_texture_no_we(game, 0, i, j);
	else if (game->u_plan.x == 1 && (game->pos.x + game->point.x) < game->pos.x 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.x_size 
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 
		&& game->map.layout[(int)(game->pos.y + game->point.y)][(int)\
		(-game->plan[game->u_plan.x][game->u_plan.y].d - 1)] == 1)
		ft_print_texture_so_ea(game, 1, i, j);
	else if (game->u_plan.x == 0 && (game->pos.y + game->point.y) > game->pos.y \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) < game->map.y_size \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) >= 0 
		&& game->map.layout[(int)(-game->plan[game->u_plan.x][game->u_plan.y].d)] \
		[(int)(game->pos.x + game->point.x)] == 1)
		ft_print_texture_no_we(game, 2, i, j);
	else
		ft_print_texture_so_ea(game, 0, i, j);
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

void ft_update_rays2(t_game *game, int u, int v)
{
	game->t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * \
		game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / game->t;
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
			}
		}
	}
}

int ft_update_rays(t_game *game, int u, int v)
{
	game->t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * \
		game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / game->t;
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
				return (1);
			}
		}
	}
	return (0);
}

void	ft_print_ceiling_floor(t_game *game, int i, int j)
{
	game->t = (game->sky.a * game->u_rays.x + game->sky.b * game->u_rays.y \
		 + game->sky.c * game->u_rays.z);
	if (game->t > 0)
		game->color = game->texture.ceiling;
	else if (game->t <= 0)
		game->color = game->texture.floor;
}

// float	intersect(t_game *game, t_plan *plan, int i, int j)
// &game->plan[1][k]

int	distance_plan(int i, int j, int plan, int k)
{
	int	res;

	res = 0;
	if (plan == 0)
		res = i - k;
	else if (plan == 1)
		res = j - k;
	if (res < 0)
		res = -res;
	return (res);
}

// distance_plan(i, j, plan, k) < distance_plan(i, j, game->u_plan.x, game->u_plan.y)

float	intersect(t_game *game, int plan, int k, int i, int j)
{
	// float	t;

	game->t = game->plan[plan][k].a * game->u_rays.x + game->plan[plan][k].b \
				 * game->u_rays.y + game->plan[plan][k].c * game->u_rays.z;
	if (game->t != 0)
	{
		game->t = -(game->plan[plan][k].a * game->pos.x + game->plan[plan][k].b * \
			game->pos.y + game->plan[plan][k].c * 0.5 + game->plan[plan][k].d) / game->t;
		if (game->t > 0)
		{
			game->point.x = game->u_rays.x * game->t;
			game->point.y = game->u_rays.y * game->t;
			game->point.z = 0.5 + game->u_rays.z * game->t;
			if (game->point.z < 1 && game->point.z > 0
				&& (int)(game->pos.x + game->point.x) >= 0 
				&& (int)(game->pos.y + game->point.y) >= 0 
				&& (int)(game->pos.x + game->point.x) <= game->map.x_size 
				&& (int)(game->pos.y + game->point.y) <= game->map.y_size)
			{
				if (ft_is_wall(game, game->map.layout, k, plan))
				{
					// if ()
					{
						game->close_t = game->t;
						game->u_plan.x = plan;
						game->u_plan.y = k;
					}
				}
			}
		}
	}
	return (game->t);
}

void	ft_search_plan_x(t_game *game, int i, int j)
{
	float	t;
	int		k;

	t = 1;
	if (game->u_rays.x < 0)
	{
		k = i;
		while (k >= 0 && t)
		{
			t = 0; //intersect(game, 1, k, i, j);
			dprintf(2, "t is %d\n", game->close_t);
			if (t == 0)
			{
				ft_print_ceiling_floor(game, i, j);
				return ;
			}
			--k;
		}
	}
	k = i;
	while (k < game->map.x_size)
	{
		t = intersect(game, 1, k, i, j);
		dprintf(2, "t is %d\n", game->close_t);
		if (t == 0)
		{
			ft_print_ceiling_floor(game, 1, k);
			return ;
		}
		++k;
	}
	// game->t = t;
	// ft_print_texture(game, i, j);
}

void	ft_search_plan_y(t_game *game, int i, int j)
{
	float	t;
	int		k;

	t = 1;
	if (game->u_rays.y < 0)
	{
		k = i;
		while (k >= 0 && t)
		{
			t = intersect(game, 0, k, i, j);
			if (t == 0)
			{
				ft_print_ceiling_floor(game, i, j);
				return ;
			}
			--k;
		}
	}
	k = i;
	while (k < game->map.y_size && t)
	{
		t = intersect(game, 0, k, i, j);
		if (t == 0)
		{
			ft_print_ceiling_floor(game, 0, k);
			return ;
		}
		++k;
	}
	// game->t = t;
	// ft_print_texture(game, i, j);
}


void	ft_switch_plan2(t_game *game, int i, int j)
{
	int v;
	int	u;
	int	switch_p;
	
	v = 0;
	while (v < 2)
	{
		if (v == 0)
			switch_p = game->map.y_size;
		else
			switch_p = game->map.x_size;
		u = 0;
		while (u <= switch_p)
		{
			game->t = (game->plan[v][u].a * game->u_rays.x + game->plan[v][u].b \
				 * game->u_rays.y + game->plan[v][u].c * game->u_rays.z);
			if (game->t != 0)
				ft_update_rays(game, u, v);
			else
				ft_print_ceiling_floor(game, i, j);
			++u;
		}
		++v;
	}
	if (game->close_t != 0 && game->u_plan.x != 3 && game->u_plan.y != -7)
		ft_print_texture(game, i, j);
}

// plan = 0 -> y
// plan = 1 -> x
// quand on parcourt les  
void	ft_switch_plan(t_game *game, int i, int j)
{
	int v;
	int	u;
	int	switch_p;
	
	v = 0;
	while (v < 1)
	{
		if (v == 0)
			switch_p = game->map.y_size;
		else
			switch_p = game->map.x_size;
		u = i;
		while (u >= 0)
		{
			game->t = (game->plan[v][u].a * game->u_rays.x + game->plan[v][u].b \
				 * game->u_rays.y + game->plan[v][u].c * game->u_rays.z);
			if (game->t != 0)
			{

				if (ft_update_rays(game, u, v))
					return ;
			}
			else
				return (ft_print_ceiling_floor(game, i, j));
			--u;
		}
		u = i;
		while (u <= switch_p)
		{
			game->t = (game->plan[v][u].a * game->u_rays.x + game->plan[v][u].b \
				 * game->u_rays.y + game->plan[v][u].c * game->u_rays.z);
			if (game->t != 0)
			{

				if (ft_update_rays(game, u, v))
					return ;
			}
			else
				return (ft_print_ceiling_floor(game, i, j));
			++u;
		}
		++v;
	}
	if (game->close_t != 0 && game->u_plan.x != 3 && game->u_plan.y != -7)
		ft_print_texture(game, i, j);
}

void	ft_printf_fps(void)
{
	if (get_time() - g_fps < 1000)
		g_frame++;
	else
	{
		ft_printf("\r\033[2KFPS: %d", g_frame);
		g_fps = get_time();
		g_frame = 0;
	}
}

void	ft_resolution(t_game *game, int i, int j)
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
			my_mlx_pixel_put(&game->view, j, i, game->color);
			++j;
		}
		++i;
	}
}

void	ft_plan_plan(t_game *game, int i, int j)
{
	ft_search_plan_x(game, i, j);
	// ft_search_plan_y(game, i, j);
	ft_print_texture(game, i, j);
}


int	ft_update_game(t_game *game)
{
	int		i;
	int		j;
	int		size;
	t_vec3d	ray_tmp;

	i = 0;
	size = 10;
	ft_move(game);
	tourn(game);
	while (i < game->mlx.win_height)
	{
		j = 0;
		while (j < game->mlx.win_width)
		{
			if (i > 10 && i < (game->map.y_size * size) + 10 && j > 10 && j < (game->map.x_size * size) + 10)
			{
				j += RESOLUTION;
				continue ;
			}
			ray_tmp.x = game->rays[i][j].x;
			ray_tmp.y = game->rays[i][j].y * cos(game->angle_x) + game->rays[i][j].z * -sin(game->angle_x);
			ray_tmp.z= game->rays[i][j].y * sin(game->angle_x) + game->rays[i][j].z * cos(game->angle_x);
			game->u_rays.x = ray_tmp.x * cos(game->angle_z) + game->rays[i][j].y * -sin(game->angle_z);
			game->u_rays.y = ray_tmp.x * sin(game->angle_z) + game->rays[i][j].y * cos(game->angle_z);
			game->u_rays.z = ray_tmp.z;
			game->close_t = 0;
			game->u_plan.x = 3;
			game->u_plan.y = -7;
			ft_switch_plan2(game, i, j);
			ft_resolution(game, i, j);
			j += RESOLUTION;
		}
		i += RESOLUTION;
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	ft_printf_fps();
	drawMap2D(game, size);
	ft_draw_circle(game, 80, 80, 70);
	return (0);
}

// plan du sol : {0, 0, 1, 0}
// plan du plafond : {0, 0, 1, -1}

