/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/05/19 12:26:05 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int64_t	g_fps;
int		g_frame;

void	ft_display_game(t_game *game)
{
	(void)game;
	return ;
}

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_update(t_game *game)
{
	int		i;
	int		j;
	int		u;
	int		v;
	float	best_t;
	int		v_plan;
	int		u_plan;
	int		switch_plan;
	float	r_v;
	float	t;
	float	x;
	float	y;
	float	point_x;
	float	point_y;
	float	point_z;
	
	t_vec3d	rays_temp;
	t_imgs	img;

	img.img_ptr = mlx_new_image(game->mlx.ptr, WIDTH, HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	x = 0;
	y = 0;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			rays_temp.x = game->rays[i][j].x * cos(game->angle_z) + game->rays[i][j].y * -sin(game->angle_z) + game->rays[i][j].z * 0; //z
			rays_temp.y = game->rays[i][j].x * sin(game->angle_z) + game->rays[i][j].y * cos(game->angle_z) + game->rays[i][j].z * 0;
			rays_temp.z = game->rays[i][j].x * 0 + game->rays[i][j].y * 0 + game->rays[i][j].z * 1;
			v = 0;
			best_t = 0;
			v_plan = 3;
			u_plan = -7;
			while (v < 2)
			{
				if (v == 0)
					switch_plan = game->map.y_size;
				else
					switch_plan = game->map.x_size;
				u = 0;
				while (u <= switch_plan)
				{
					t = (game->plan[v][u].a * rays_temp.x  + game->plan[v][u].b * rays_temp.y + game->plan[v][u].c * rays_temp.z);
					if (t != 0)
					{
						t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / t;
						if (t > 0)
						{
							point_x = rays_temp.x * t;
							point_y = rays_temp.y * t;
							point_z = 0.5 + rays_temp.z * t;
							if (point_z < 1 && point_z > 0 && (int)(game->pos.x + point_x) >= 0 && (int)(game->pos.y + point_y) >= 0 && (int)(game->pos.x + point_x) < game->map.x_size && (int)(game->pos.y + point_y) < game->map.y_size)
							{
								if ((best_t == 0 || t < best_t) && ((v == 0 && (game->pos.y + point_y) < game->pos.y && (int)(-game->plan[v][u].d) < game->map.y_size && (int)(-game->plan[v][u].d - 1) >= 0 && game->map.layout[(int)(-game->plan[v][u].d - 1)][(int)(game->pos.x + point_x)] == 1)
								|| (v == 1 && (game->pos.x + point_x) < game->pos.x && (int)(-game->plan[v][u].d - 1) < game->map.x_size && (int)(-game->plan[v][u].d - 1) >= 0 && game->map.layout[(int)(game->pos.y + point_y)][(int)(-game->plan[v][u].d - 1)] == 1)
								|| (v == 0 && (game->pos.y + point_y) > game->pos.y && (int)(-game->plan[v][u].d) < game->map.y_size && (int)(-game->plan[v][u].d) >= 0 && game->map.layout[(int)(-game->plan[v][u].d)][(int)(game->pos.x + point_x)] == 1)
								|| (v == 1 && (game->pos.x + point_x) > game->pos.x && (int)(-game->plan[v][u].d) < game->map.x_size && (int)(-game->plan[v][u].d) >= 0 && game->map.layout[(int)(game->pos.y + point_y)][(int)(-game->plan[v][u].d)] == 1)))
								{
									best_t = t;
									v_plan = v;
									u_plan = u;
								}
							}
						}
					}
					u++;
				}
				v++;
			}
		if (best_t != 0 && v_plan != 3 && u_plan != - 7)
			{
				point_x = rays_temp.x * best_t;
				point_y = rays_temp.y * best_t;
				point_z = 0.5 + rays_temp.z * best_t;
				if (v_plan == 0 && (game->pos.y + point_y) < game->pos.y && (int)(-game->plan[v_plan][u_plan].d - 1) < game->map.y_size && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map.layout[(int)(-game->plan[v_plan][u_plan].d - 1)][(int)(game->pos.x + point_x)] == 1)
					img.data[i * WIDTH + j] = RED;
				else if (v_plan == 1 && (game->pos.x + point_x) < game->pos.x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->map.x_size && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map.layout[(int)(game->pos.y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 1)
					img.data[i * WIDTH + j] = DARK_RED;
				else if (v_plan == 0 && (game->pos.y + point_y) > game->pos.y && (int)(-game->plan[v_plan][u_plan].d) < game->map.y_size && (int)(-game->plan[v_plan][u_plan].d) >= 0 && game->map.layout[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->pos.x + point_x)] == 1)
					img.data[i * WIDTH + j] = 0x90fff2;
				else
					img.data[i * WIDTH + j] = DARK_RED;
			}
			y = 0;
			t = 0;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, img.img_ptr, 0, 0);
	mlx_destroy_image(game->mlx.ptr, img.img_ptr);
	if (get_time() - g_fps < 1000)
		g_frame++;
	else
	{
		ft_printf("\033[2K\rFPS: %d\e[0m\n", g_frame);
		g_fps = get_time();
		g_frame = 0;
	}
	return (0);
}
