/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/05/25 16:20:15 by lboudjem         ###   ########.fr       */
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

	dst = (char *) img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

int	ft_print_texture_no_we(t_game *game, int wall, int i, int j)
{
	int x;
	int	y;
	int color;

	x = 0;
	y = 0;
	x = (int)(((game->pos.x + game->point.x) - (int)(game->pos.x + game->point.x)) * game->texture.wall[wall].width);
	y = game->texture.wall[wall].height - (int)((game->point.z - (int)(game->point.z)) * game->texture.wall[wall].height) - 1;
	color = *(unsigned int *)(game->texture.wall[wall].addr + y * game->texture.wall[wall].ll + x * (game->texture.wall[wall].bpp / 8));
	my_mlx_pixel_put(&game->view, j, i, color);
	return (color);
}

void	ft_print_texture_so_ea(t_game *game, int wall, int i, int j)
{
	int	x;
	int	y;
	int color;

	x = 0;
	y = 0;
	x = (int)(((game->pos.y + game->point.y) - (int)(game->pos.y + game->point.y)) * game->texture.wall[1].width);
	y = game->texture.wall[1].height - (int)((game->point.z - (int)(game->point.z)) * game->texture.wall[1].height) - 1;
	color = *(unsigned int *)(game->texture.wall[1].addr + y * game->texture.wall[1].ll + x * (game->texture.wall[1].bpp / 8));
	my_mlx_pixel_put(&game->view, j, i, color); //dark
}

void	ft_print_texture(t_game *game, int i, int j)
{
	game->point.x = game->u_rays.x * game->close_t;
	game->point.y = game->u_rays.y * game->close_t;
	game->point.z = 0.5 + game->u_rays.z * game->close_t;
	if (game->u_plan.x == 0 && (game->pos.y + game->point.y) < game->pos.y && \
		(int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < game->map.y_size \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) >= 0 && \
		game->map.layout[(int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1)] \
		[(int)(game->pos.x + game->point.x)] == 1)	
		ft_print_texture_no_we(game, 0, i, j);
	else if (game->u_plan.x == 1 && (game->pos.x + game->point.x) < game->pos.x \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) < \
		game->map.x_size && (int)(-game->plan[game->u_plan.x][game->u_plan.y].d - 1) \
		>= 0 && game->map.layout[(int)(game->pos.y + game->point.y)][(int)\
		(-game->plan[game->u_plan.x][game->u_plan.y].d - 1)] == 1)
		ft_print_texture_so_ea(game, 1, i, j);
	else if (game->u_plan.x == 0 && (game->pos.y + game->point.y) > game->pos.y \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) < game->map.y_size \
		&& (int)(-game->plan[game->u_plan.x][game->u_plan.y].d) >= 0 && \
		game->map.layout[(int)(-game->plan[game->u_plan.x][game->u_plan.y].d)] \
		[(int)(game->pos.x + game->point.x)] == 1)
		ft_print_texture_no_we(game, 2, i, j);
	else
		ft_print_texture_so_ea(game, 0, i, j);
}

int	ft_update_game(t_game *game)
{
	int		i;
	int		j;
	int		u;
	int		v;
	int		switch_p;

	game->view.id = mlx_new_image(game->mlx.ptr, game->mlx.win_width, game->mlx.win_height);
	game->view.addr = mlx_get_data_addr(game->view.id, &game->view.bpp, &game->view.ll, &game->view.endian);
	i = 0;
	while (i < game->mlx.win_height)
	{
		j = 0;
		while (j < game->mlx.win_width)
		{
			game->u_rays.x = game->rays[i][j].x * cos(game->angle_z) + game->rays[i][j].y * -sin(game->angle_z);
			game->u_rays.y = game->rays[i][j].x * sin(game->angle_z) + game->rays[i][j].y * cos(game->angle_z);
			game->u_rays.z = game->rays[i][j].z;
			v = 0;
			game->close_t = 0;
			game->u_plan.x = 3;
			game->u_plan.y = -7;
			while (v < 2)
			{
				if (v == 0)
					switch_p = game->map.y_size;
				else
					switch_p = game->map.x_size;
				u = 0;
				while (u <= switch_p)
				{
					game->t = (game->plan[v][u].a * game->u_rays.x + game->plan[v][u].b * game->u_rays.y + game->plan[v][u].c * game->u_rays.z);
					if (game->t != 0)
					{
						game->t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / game->t;
						if (game->t > 0)
						{
							game->point.x = game->u_rays.x * game->t;
							game->point.y = game->u_rays.y * game->t;
							game->point.z = 0.5 + game->u_rays.z * game->t;
							if (game->point.z < 1 && game->point.z > 0 && (int)(game->pos.x + game->point.x) >= 0 && (int)(game->pos.y + game->point.y) >= 0 && (int)(game->pos.x + game->point.x) < game->map.x_size && (int)(game->pos.y + game->point.y) < game->map.y_size)
							{
								if ((game->close_t == 0 || game->t < game->close_t) && ((v == 0 && (game->pos.y + game->point.y) < game->pos.y && (int)(-game->plan[v][u].d) < game->map.y_size && (int)(-game->plan[v][u].d - 1) >= 0 && game->map.layout[(int)(-game->plan[v][u].d - 1)][(int)(game->pos.x + game->point.x)] == 1)
								|| (v == 1 && (game->pos.x + game->point.x) < game->pos.x && (int)(-game->plan[v][u].d - 1) < game->map.x_size && (int)(-game->plan[v][u].d - 1) >= 0 && game->map.layout[(int)(game->pos.y + game->point.y)][(int)(-game->plan[v][u].d - 1)] == 1)
								|| (v == 0 && (game->pos.y + game->point.y) > game->pos.y && (int)(-game->plan[v][u].d) < game->map.y_size && (int)(-game->plan[v][u].d) >= 0 && game->map.layout[(int)(-game->plan[v][u].d)][(int)(game->pos.x + game->point.x)] == 1)
								|| (v == 1 && (game->pos.x + game->point.x) > game->pos.x && (int)(-game->plan[v][u].d) < game->map.x_size && (int)(-game->plan[v][u].d) >= 0 && game->map.layout[(int)(game->pos.y + game->point.y)][(int)(-game->plan[v][u].d)] == 1)))
								{
									game->close_t = game->t;
									game->u_plan.x = v;
									game->u_plan.y = u;
								}
							}
						}
					}
					else
					{
						game->t = (game->sky.a * game->u_rays.x + game->sky.b * game->u_rays.y + game->sky.c * game->u_rays.z);
						if (game->t > 0)
							my_mlx_pixel_put(&game->view, j, i, game->texture.ceiling);
						else if (game->t <= 0)
							my_mlx_pixel_put(&game->view, j, i, game->texture.floor);
					}
					u++;
				}
				v++;
			}
			if (game->close_t != 0 && game->u_plan.x != 3 && game->u_plan.y != -7)
				ft_print_texture(game, i, j);
			game->t = 0;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	if (get_time() - g_fps < 1000)
		g_frame++;
	else
	{
		// ft_printf("\033[2K\rFPS: %d\e[0m\n", g_frame);
		g_fps = get_time();
		g_frame = 0;
	}
	return (0);
}

// plan du sol : {0, 0, 1, 0}
// plan du plafond : {0, 0, 1, -1}

