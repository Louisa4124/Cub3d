/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/06/18 17:45:37 by tlegrand         ###   ########.fr       */
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

float	distance_plan(t_vec3d u, t_vec3d v)
{
	float	x;
	float	y;
	float	z;

	x = v.x - u.x;
	y = v.y - u.y;
	z = v.z - u.z;
	return ((sqrt(x * x) + (y * y) + (z * z)));
}

int ft_update_rays(t_game *game, int u, int v, int wit)
{
	game->t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * \
		game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / game->t;
	if (game->t > game->close_t && wit == 0)
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

void	ft_print_ceiling_floor(t_game *game, int i, int j)
{
	game->t = (game->sky.a * game->u_rays.x + game->sky.b * game->u_rays.y \
		 + game->sky.c * game->u_rays.z);
	if (game->t > 0)
		game->color = game->texture.ceiling;
	else if (game->t <= 0)
		game->color = game->texture.floor;
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
				ft_update_rays2(game, u, v);
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
// i -> y         j -> x


int	ft_intersect(t_game *game, int pos, int max, int plan, int found)
{
	int	u;
	int	wit;

	u = pos;
	wit = 1;
	while (u >= 0 && wit > 0)
	{
		game->t = (game->plan[plan][u].a * game->u_rays.x + game->plan[plan][u].b \
				* game->u_rays.y + game->plan[plan][u].c * game->u_rays.z);
		if (game->t != 0)
			wit = ft_update_rays(game, u, plan, found);
		--u;
	}
	u = pos;
	while (u <= max && wit > 0)
	{
		game->t = (game->plan[plan][u].a * game->u_rays.x + game->plan[plan][u].b \
				* game->u_rays.y + game->plan[plan][u].c * game->u_rays.z);
		if (game->t != 0)
			wit = ft_update_rays(game, u, plan, found);
		++u;
	}
	return (wit);
}


void	ft_switch_plan(t_game *game, int i, int j)
{
	int	wit_y;
	int	wit_x;

	wit_y = ft_intersect(game, game->pos.y, game->map.y_size, 0, 1);
	wit_x = ft_intersect(game, game->pos.x, game->map.x_size, 1, wit_y);
	
	if (wit_y == 0 || wit_x == 0)
		ft_print_texture(game, i, j);
	else
		ft_print_ceiling_floor(game, i, j);

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

int	ft_update_game(t_game *game)
{
	int		i;
	int		j;
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
			game->u_plan.x = 3;
			game->u_plan.y = -7;
			ft_switch_plan(game, i, j);
			ft_resolution(game, i, j);
			j += RESOLUTION;
		}
		i += RESOLUTION;
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	ft_printf_fps();
	return (0);
}

// plan du sol : {0, 0, 1, 0}
// plan du plafond : {0, 0, 1, -1}

