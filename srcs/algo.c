/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/05/11 16:55:08 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int64_t	g_fps;
int		g_frame;
int		g_lframe;

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
	float	r_h;
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
	
	t_vec3d	rayon_temp;
	t_img	img;

	img.id = mlx_new_image(game->mlx.ptr, WIDTH, HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.id, &img.bpp, &img.ll, &img.endian);
	x = 0;
	y = 0;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			rayon_temp.x = game->rays[i][j].x * cos(game->angle_z) + game->rays[i][j].y * -sin(game->angle_z) + game->rays[i][j].z * 0;
			rayon_temp.y = game->rays[i][j].x * sin(game->angle_z) + game->rays[i][j].y * cos(game->angle_z) + game->rays[i][j].z * 0;
			rayon_temp.z = game->rays[i][j].x * 0 + game->rays[i][j].y * 0 + game->rays[i][j].z * 1;
			v = 0;
			best_t = 0;
			v_plan = 3;
			u_plan = -7;
			while (v < 2)
			{
				if (v == 0)
					switch_plan = H;
				else
					switch_plan = W;
				u = 0;
				while (u <= switch_plan)
				{
					t = (game->plan[v][u].a * rayon_temp.x + game->plan[v][u].b * rayon_temp.y + game->plan[v][u].c * rayon_temp.z);
					if (t != 0)
					{
						t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / t;
						if (t > 0)
						{
							point_x = rayon_temp.x * t;
							point_y = rayon_temp.y * t;
							point_z = 0.5 + rayon_temp.z * t;
							if (point_z < 1 && point_z > 0 && (int)(game->pos.x + point_x) >= 0 && (int)(game->pos.y + point_y) >= 0 && (int)(game->pos.x + point_x) < W && (int)(game->pos.y + point_y) < H)
							{
								if ((best_t == 0 || t < best_t) && ((v == 0 && (game->pos.y + point_y) < game->pos.y && (int)(-game->plan[v][u].d) < H && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(-game->plan[v][u].d - 1)][(int)(game->pos.x + point_x)] == '1')
								|| (v == 1 && (game->pos.x + point_x) < game->pos.x && (int)(-game->plan[v][u].d - 1) < W && (int)(-game->plan[v][u].d - 1) >= 0 && game->map[(int)(game->pos.y + point_y)][(int)(-game->plan[v][u].d - 1)] == '1')
								|| (v == 0 && (game->pos.y + point_y) > game->pos.y && (int)(-game->plan[v][u].d) < H && (int)(-game->plan[v][u].d) >= 0 && game->map[(int)(-game->plan[v][u].d)][(int)(game->pos.x + point_x)] == '1')
								|| (v == 1 && (game->pos.x + point_x) > game->pos.x && (int)(-game->plan[v][u].d) < W && (int)(-game->plan[v][u].d) >= 0 && game->map[(int)(game->pos.y + point_y)][(int)(-game->plan[v][u].d)] == '1')))
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
				point_x = rayon_temp.x * best_t;
				point_y = rayon_temp.y * best_t;
				point_z = 0.5 + rayon_temp.z * best_t; // Si pas besoin de le stocker le mettre directement dans le if
				if (v_plan == 0 && (game->pos.y + point_y) < game->pos.y && (int)(-game->plan[v_plan][u_plan].d - 1) < H && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d - 1)][(int)(game->pos.x + point_x)] == '1')
					img.data[i * WIDTH + j] = 0xfce5cd; //beige
				else if (v_plan == 1 && (game->pos.x + point_x) < game->pos.x && (int)(-game->plan[v_plan][u_plan].d - 1) < W && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map[(int)(game->pos.y + point_y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == '1')
				{
					int	x, y;
					float	fx, fy;
					x = (int)(((int)(point_y) - point_y) * game->img_n.ll * 0.25); // * 0.25 car y a 64 * 4 pixels
					y = (int)(((int)(point_z) - point_z) * game->img_n.ll * 0.25);
					y = -y;
					x = -x;
					//printf("x : %d y : %d | size : %d | color : 0x%08.8X\n", x, y, (int)(game->img_n.ll * 0.25), game->img_n.data[(int)(x * (game->img_n.ll * 0.25) + y)]);
					img.data[i * WIDTH + j] = game->img_n.data[(int)(y * (game->img_n.ll * 0.25) + x)];
				}
				else if (v_plan == 0 && (game->pos.y + point_y) > game->pos.y && (int)(-game->plan[v_plan][u_plan].d) < H && (int)(-game->plan[v_plan][u_plan].d) >= 0 && game->map[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->pos.x + point_x)] == '1')
					img.data[i * WIDTH + j] = 0x90fff2; // bleu clair
				else
					img.data[i * WIDTH + j] = 0xcaffa0; //vert clair
			}
			y = 0;
			t = 0;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, img.id, 0, 0);
	mlx_destroy_image(game->mlx.ptr, img.id);
	if (get_time() - g_fps < 1000)
	{
		g_frame++;
	}
	else
	{
		ft_printf("\033[2K\r");
		dprintf(1, "FPS: %d - POS: x - %f | y - %f - Angle : %f", g_frame, game->pos.x, game->pos.y, game->angle_z);
		ft_printf("\e[0m");
		g_lframe = g_frame;
		g_fps = get_time();
		g_frame = 0;
	}
	char *test;
	test = ft_itoa(g_lframe);
	mlx_string_put(game->mlx.ptr, game->mlx.win, 2, 10, 0xffffff, "FPS: ");
	mlx_string_put(game->mlx.ptr, game->mlx.win, 30, 10, 0xffffff, test);
	free(test);
	return (0);
}
