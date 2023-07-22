/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/22 14:24:47 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *) img->addr + (y * img->ll + x * (img->bpp >> 3));
	*(unsigned int *) dst = color;
}

static void	ft_resolution(t_game *game, int i, int j, int color)
{
	int	x;
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

void	ft_display_menu(t_game *game)
{
	unsigned int	*image_data;

	game->pause = 1;
	image_data = (unsigned int *)game->view.addr;
	blur_image(&game->view, image_data);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->button.id, 350, \
		100);
}

static void	display_game(t_game *game, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->mlx.win_height)
	{
		j = 0;
		while (j < game->mlx.win_width)
		{
			if (i > 10 && i < (game->map.y_size * size) + 10 && j > 10 && \
				j < (game->map.x_size * size) + 10)
			{
				j += RESOLUTION;
				continue ;
			}
			game->u_rays = ft_rotate_vec_z(ft_rotate_vec_x(game->rays[i][j], \
				game->angle_x), game->angle_z);
			game->close_t = 0;
			ft_resolution(game, i, j, switch_plan_algo(game));
			j += RESOLUTION;
		}
		i += RESOLUTION;
	}
}

void	*routine(void *data)
{
	t_game	*game;

	game = data;
	display_game(game, MINIMAP_SIZE);
	return (NULL);
}

int	update_game(t_game *game)
{
	pthread_t	pid;

	if (game->pause == 1)
		return (0);
	view_update_pos(game);
	view_update_dir_key(game);
	view_update_dir_mouse(game);
	if (pthread_create(&pid, NULL, routine, game))
		dprintf(2, " ER THR\n");
	// display_game(game, MINIMAP_SIZE);
	if (pthread_join(pid, NULL))
		dprintf(2, " ER JN\n");
	draw_map(game, MINIMAP_SIZE);
	ft_printf_fps(1);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	return (0);
}
