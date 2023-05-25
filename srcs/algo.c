/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:29:53 by louisa            #+#    #+#             */
/*   Updated: 2023/05/25 13:21:49 by lboudjem         ###   ########.fr       */
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

// void	my_mlx_pixel_put(t_game *game, const int x, const int y, int color)
// {
// 	char	*dst;

// 	dst = game->addr + (y * game->ll + x * (game->bpp / 8));
// 	*(unsigned int *)dst = color;
// }

void	tourn(t_game *game)
{
	int	x_quarter;
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
	// dprintf(2, "mouse : x : %d, y : %d\n", x, y);
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

void	my_mlx_pixel_put(t_imgs *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *) img->data + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
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
	float	t;
	int	x, y = 0;
	int color;
	t_vec3d	point;
	t_plan	sky;
	t_vec3d	rays_temp;
	t_imgs	img;

	img.img_ptr = mlx_new_image(game->mlx.ptr, game->mlx.win_width, game->mlx.win_height);
	img.data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	i = 0;
	sky.a = 0;
	sky.b = 0;
	sky.c = 1;
	sky.d = -1;
	while (i < game->mlx.win_height)
	{
		j = 0;
		while (j < game->mlx.win_width)
		{
			rays_temp.x = game->rays[i][j].x * cos(game->angle_z) + game->rays[i][j].y * -sin(game->angle_z);
			rays_temp.y = game->rays[i][j].x * sin(game->angle_z) + game->rays[i][j].y * cos(game->angle_z);
			rays_temp.z = game->rays[i][j].z;
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
					t = (game->plan[v][u].a * rays_temp.x + game->plan[v][u].b * rays_temp.y + game->plan[v][u].c * rays_temp.z);
					if (t != 0)
					{
						t = -(game->plan[v][u].a * game->pos.x + game->plan[v][u].b * game->pos.y + game->plan[v][u].c * 0.5 + game->plan[v][u].d) / t;
						if (t > 0)
						{
							point.x = rays_temp.x * t;
							point.y = rays_temp.y * t;
							point.z = 0.5 + rays_temp.z * t;
							if (point.z < 1 && point.z > 0 && (int)(game->pos.x + point.x) >= 0 && (int)(game->pos.y + point.y) >= 0 && (int)(game->pos.x + point.x) < game->map.x_size && (int)(game->pos.y + point.y) < game->map.y_size)
							{
								if ((best_t == 0 || t < best_t) && ((v == 0 && (game->pos.y + point.y) < game->pos.y && (int)(-game->plan[v][u].d) < game->map.y_size && (int)(-game->plan[v][u].d - 1) >= 0 && game->map.layout[(int)(-game->plan[v][u].d - 1)][(int)(game->pos.x + point.x)] == 1)
								|| (v == 1 && (game->pos.x + point.x) < game->pos.x && (int)(-game->plan[v][u].d - 1) < game->map.x_size && (int)(-game->plan[v][u].d - 1) >= 0 && game->map.layout[(int)(game->pos.y + point.y)][(int)(-game->plan[v][u].d - 1)] == 1)
								|| (v == 0 && (game->pos.y + point.y) > game->pos.y && (int)(-game->plan[v][u].d) < game->map.y_size && (int)(-game->plan[v][u].d) >= 0 && game->map.layout[(int)(-game->plan[v][u].d)][(int)(game->pos.x + point.x)] == 1)
								|| (v == 1 && (game->pos.x + point.x) > game->pos.x && (int)(-game->plan[v][u].d) < game->map.x_size && (int)(-game->plan[v][u].d) >= 0 && game->map.layout[(int)(game->pos.y + point.y)][(int)(-game->plan[v][u].d)] == 1)))
								{
									best_t = t;
									v_plan = v;
									u_plan = u;
								}
							}
						}
					}
					else
					{
						t = (sky.a * rays_temp.x + sky.b * rays_temp.y + sky.c * rays_temp.z);
						if (t > 0)
							my_mlx_pixel_put(&img, j, i, game->texture.ceiling);
							// img.data[i * game->mlx.win_width + j] = game->texture.ceiling;
						if (t <= 0)
							my_mlx_pixel_put(&img, j, i, game->texture.floor);
							// img.data[i * game->mlx.win_width + j] = game->texture.floor;
					}
					u++;
				}
				v++;
			}
			if (best_t != 0 && v_plan != 3 && u_plan != -7)
			{
				point.x = rays_temp.x * best_t;
				point.y = rays_temp.y * best_t;
				point.z = 0.5 + rays_temp.z * best_t;
				if (v_plan == 0 && (game->pos.y + point.y) < game->pos.y && (int)(-game->plan[v_plan][u_plan].d - 1) < game->map.y_size && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map.layout[(int)(-game->plan[v_plan][u_plan].d - 1)][(int)(game->pos.x + point.x)] == 1)
				{
					x = (int)(((game->pos.x + point.x) - (int)(game->pos.x + point.x)) * game->texture.wall[0].width);
					y = game->texture.wall[0].height - (int)((point.z - (int)(point.z)) * game->texture.wall[0].height) - 1;
					color = *(unsigned int *)(game->texture.wall[0].addr + y * game->texture.wall[0].ll + x * (game->texture.wall[0].bpp / 8));
					my_mlx_pixel_put(&img, j, i, color);
				}
				else if (v_plan == 1 && (game->pos.x + point.x) < game->pos.x && (int)(-game->plan[v_plan][u_plan].d - 1) < game->map.x_size && (int)(-game->plan[v_plan][u_plan].d - 1) >= 0 && game->map.layout[(int)(game->pos.y + point.y)][(int)(-game->plan[v_plan][u_plan].d - 1)] == 1)
				{
					x = (int)(((game->pos.y + point.y) - (int)(game->pos.y + point.y)) * game->texture.wall[1].width);
					y = game->texture.wall[1].height - (int)((point.z - (int)(point.z)) * game->texture.wall[1].height) - 1;
					color = *(unsigned int *)(game->texture.wall[1].addr + y * game->texture.wall[1].ll + x * (game->texture.wall[1].bpp / 8));
					my_mlx_pixel_put(&img, j, i, color); //dark
				}
				else if (v_plan == 0 && (game->pos.y + point.y) > game->pos.y && (int)(-game->plan[v_plan][u_plan].d) < game->map.y_size && (int)(-game->plan[v_plan][u_plan].d) >= 0 && game->map.layout[(int)(-game->plan[v_plan][u_plan].d)][(int)(game->pos.x + point.x)] == 1)
				{
					x = (int)(((game->pos.x + point.x) - (int)(game->pos.x + point.x)) * game->texture.wall[2].width);
					y = game->texture.wall[2].height - (int)((point.z - (int)(point.z)) * game->texture.wall[2].height) - 1;
					color = *(unsigned int *)(game->texture.wall[2].addr + y * game->texture.wall[2].ll + x * (game->texture.wall[2].bpp / 8));
					my_mlx_pixel_put(&img, j, i, color);
				}
				else
				{
					x = (int)(((game->pos.y + point.y) - (int)(game->pos.y + point.y)) * game->texture.wall[3].width);
					y = game->texture.wall[3].height - (int)((point.z - (int)(point.z)) * game->texture.wall[3].height) - 1;
					color = *(unsigned int *)(game->texture.wall[3].addr + y * game->texture.wall[3].ll + x * (game->texture.wall[3].bpp / 8));
					my_mlx_pixel_put(&img, j, i, color); //dark
				}
			}
			t = 0;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, img.img_ptr, 0, 0);
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

