/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/06/30 15:45:34 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int64_t	g_fps;
int		g_frame;

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
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

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *) img->addr + (y * img->ll + x * (img->bpp >> 3));
	*(unsigned int *) dst = color;
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
			ft_mlx_pixel_put(&game->view, j, i, color);
			++j;
		}
		++i;
	}
}

int	display_game(t_game *game)
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
			ray_tmp = ft_rotate_vec_x(game->rays[i][j], game->angle_x);
			game->u_rays = ft_rotate_vec_z(ray_tmp, game->angle_z);
			game->close_t = 0;
			color = k_plan_algo(game);
			ft_resolution(game, i, j, color);
			j += RESOLUTION;
		}
		i += RESOLUTION;
	}
	drawMap2D(game, size);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	// ft_printf_fps();
	return (0);
}
