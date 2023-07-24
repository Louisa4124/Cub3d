/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/07/24 22:40:16 by louisa           ###   ########.fr       */
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

// void	ft_display_menu(t_game *game)
// {
//     int i;
    
//     while (game->pause == 2)
//     {
//         i = 0;
//         while (i < 4)
//         {
//             mlx_clear_window(game->mlx.ptr, game->mlx.win);
//             printf("oui\n");
//             mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[i].id, 0, 0);
//             mlx_do_sync(game->mlx.ptr);
//             usleep(1000000);
//             ++i;
//         }
//     }
// }

void    ft_display_menu(t_game *game)
{
    static int  i = 0;
    int 		x;
	int 		y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
    if (game->ms >= 1)
    {
        i++;
        game->ms -= 1;
    }
    if (i >= 15)
        i = 0;
    mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[i].id, 0, 0);
    mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[15].id, 179, 101);
    if ((x > 510 && x < 580) && (y > 370 && y < 400))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[16].id, 179, 101);
    if ((x > 470 && x < 630) && (y > 445 && y < 470))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[17].id, 179, 101);
	if ((x > 500 && x < 580) && (y > 520 && y < 550))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[18].id, 179, 101);
}

void	ft_display_settings(t_game *game)
{
    static int  i = 0;
    int 		x;
	int 		y;

	mlx_mouse_get_pos(game->mlx.ptr, game->mlx.win, &x, &y);
    if (game->ms >= 1)
    {
        i++;
        game->ms -= 1;
    }
    if (i >= 15)
        i = 0;
    mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[i].id, 0, 0);
    mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[19].id, 179, 101);
    if ((x > 310 && x < 390) && (y > 400 && y < 425))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[20].id, 179, 101);
    if ((x > 480 && x < 610) && (y > 400 && y < 425))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[21].id, 179, 101);
	if ((x > 715 && x < 780) && (y > 400 && y < 425))
    	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->animation[22].id, 179, 101);
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
	game->ms += 0.0015;
	return (0);
}
