/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/24 15:45:49 by lboudjem         ###   ########.fr       */
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

	x = i + game->resolution;
	y = j + game->resolution;
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

void	ft_display_pause(t_game *game)
{
	unsigned int	*image_data;

	game->pause = 1;
	image_data = (unsigned int *)game->view.addr;
	blur_image(&game->view, image_data);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->view.id, 0, 0);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->button.id, 200, \
		50);
}

void    ft_display_menu(t_game *game)
{
    static int  i = 0;
    int 		x;
	int 		y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
    if ((x > 135 && x < 225) && (y > 230 && y < 250))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[5].id, 0, 0);
    else if ((x > 95 && x < 260) && (y > 290 && y < 305))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[6].id, 0, 0);
	else if ((x > 140 && x < 215) && (y > 335 && y < 360))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[7].id, 0, 0);
	else 
	{
		if (game->ms >= 1)
		{
			i++;
			game->ms -= 1;
		}
		if (i >= 4)
			i = 0;
		mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[i].id, 0, 0);
	}
}

void	ft_display_settings(t_game *game)
{
	static int  i = 0;

	//printf("ms = %f\n", game->ms);
	if (game->ms >= 0.5)
	{
		i++;
		game->ms -= 0.5;
	}
	if (i >= 10)
		i = 0;
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation2[i].id, 0, 0);
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
				j += game->resolution;
				continue ;
			}
			game->u_rays = ft_rotate_vec_z(ft_rotate_vec_x(game->rays[i][j], \
				game->angle_x), game->angle_z);
			game->close_t = 0;
			ft_resolution(game, i, j, switch_plan_algo(game));
			j += game->resolution;
		}
		i += game->resolution;
	}
}

int	update_game(t_game *game)
{
    float	time_frame;

    time_frame = 1 / ft_get_fps();
    if (game->pause == 2)
        ft_display_menu(game);
	if (game->pause == 1)
		ft_display_settings(game);
	if (game->pause == 0)
	{
		view_update_pos(game);
		view_update_dir_key(game);
		view_update_dir_mouse(game);
		display_game(game, MINIMAP_SIZE);
		draw_map(game, MINIMAP_SIZE);
		mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
			game->view.id, 0, 0);
	}
	ft_printf_fps(0);
	//printf("get_fps = %d\n", ft_get_fps());
	game->ms += time_frame;
	return (0);
}
