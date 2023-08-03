/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:12 by tlegrand          #+#    #+#             */
/*   Updated: 2023/08/03 21:19:55 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->ll + x * (img->bpp >> 3));
	*(unsigned int *) dst = color;
}

static void	ft_resolution(t_tmp *data, int i, int j, int color)
{
	int	max_y;
	int	max_x;
	int	j_start;

	max_y = i + RESOLUTION;
	max_x = j + RESOLUTION;
	j_start = j;
	while (i < max_y && i < data->area->end_y)
	{
		j = j_start;
		while (j < max_x && j < data->area->end_x)
		{
			ft_mlx_pixel_put(data->link->view, j, i, color);
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

void	display_game(void *ptr, void *area)
{
	t_tmp		data;
	int			i;
	int			j;

	data.area = area;
	data.link = ptr;
	i = data.area->start_y;
	while (i < data.area->end_y - SEE_TH)
	{
		j = data.area->start_x;
		while (j < data.area->end_x)
		{
			if (i > 10 && i < (data.link->map->y_size * MINIMAP_SIZE) + 10 && j > 10 && \
				j < data.link->map->x_size * MINIMAP_SIZE + 10)
			{
				j = data.link->map->x_size * MINIMAP_SIZE + 10;
				continue ;
			}
			data.tmp_rays = ft_rotate_vec_z(ft_rotate_vec_x(data.link->rays[i][j], \
				*data.link->angle_x), *data.link->angle_z);
			data.close_t = 0;
			ft_resolution(&data, i, j, switch_plan_algo(&data));
			j += RESOLUTION;
		}
		i += RESOLUTION;
	}
}


int	update_game(t_game *game)
{
	int	i;

	if (game->pause == 1)
		return (0);
	view_update_pos(game);
	view_update_dir_key(game);
	view_update_dir_mouse(game);
	// th_print(&game->m_print, "start launching th", 0);
	pthread_mutex_lock(&game->m_queue);
	(*game->queue) = (*game->queue)->next;
	pthread_mutex_unlock(&game->m_queue);
	i = -1;
	while (++i < N_JOB)
		sem_post(&game->sem_thread);
	// th_print(&game->m_print, "waiting for Th", 0);
	i = -1;
	while (++i < N_JOB)
		sem_wait(&game->sem_main);
	// draw_map(&game->link, NULL);
	ft_printf_fps(1);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, \
		game->view.id, 0, 0);
	return (0);
}

/*
void	*mlx_new_fullscreen_window(t_xvar *xvar, int *size_x, int *size_y,
		char *title)
{
	t_win_list				*new_win;
	XSetWindowAttributes	xswa;

	if (!(new_win = malloc(sizeof(*new_win))))
		return ((void *)0);
	xswa = get_default_attributes(xvar);
	xswa.override_redirect = 1;
	mlx_get_screen_size(xvar, size_x, size_y);
	new_win->window = XCreateWindow(xvar->display, xvar->root, 0, 0, *size_x,
			*size_y, 0, CopyFromParent, InputOutput, xvar->visual,
			CWEventMask | CWBackPixel | CWBorderPixel | CWColormap | CWOverrideRedirect,
			&xswa);
	return (set_configs(xvar, new_win, *size_x, *size_y, title));
}
*/

/*

  a -> b -> ... -> end (NULL) -> a
 /\
 |
HEAD

struct	job
{
	int			jid;
	void		*data;
	void		*func;
	struct job	*next;	
}



*/