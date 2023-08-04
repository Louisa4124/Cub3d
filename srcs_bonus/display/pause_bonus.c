/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:50:43 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/04 16:15:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	load_img(t_game *game, t_vec2d i, char *path, int s, int nb_frame)
{
	game->anim[i.x][i.y].id = mlx_xpm_file_to_image(game->mlx.ptr, \
		path, &game->anim[i.x][i.y].width, &game->anim[i.x][i.y].height);
	if (game->anim[i.x][i.y].id == NULL)
		return (ft_putstr_fd("Error\nCan't load texture\n", 2), 1);
	game->anim[i.x][i.y].addr = mlx_get_data_addr(game->anim[i.x][i.y].id, \
		&game->anim[i.x][i.y].bpp, &game->anim[i.x][i.y].ll, &game->anim[i.x][i.y].endian);
	if (game->anim[i.x][i.y].addr == NULL)
		return (ft_putstr_fd("Error\nCan't get texture data\n", 2), 1);
	game->sprite[s].x = 0;
	game->sprite[s].y = 0;
	game->sprite[s].frame = nb_frame;
	game->sprite[s].img = &game->anim[i.x][i.y];
	return (0); 
}

int	load_menu(t_game *game, int i, int j, char *path)
{
	game->anim[i][j].id = mlx_xpm_file_to_image(game->mlx.ptr, \
		path, &game->anim[i][j].width, &game->anim[i][j].height);
	if (game->anim[i][j].id == NULL)
		return (ft_putstr_fd("Error\nCan't load texture\n", 2), 1);
	game->anim[i][j].addr = mlx_get_data_addr(game->anim[i][j].id, \
		&game->anim[i][j].bpp, &game->anim[i][j].ll, &game->anim[i][j].endian);
	if (game->anim[i][j].addr == NULL)
		return (ft_putstr_fd("Error\nCan't get texture data\n", 2), 1);
	return (0); 
}

/*
int	load_img(t_game *g, t_vec2d i, char *path, int s, int nb_frame)
{
	g->anim[i.x][i.y].id = mlx_xpm_file_to_image(g->mlx.ptr, \
		path, &g->anim[i.x][i.y].width, &g->anim[i.x][i.y].height);
	if (g->anim[i.x][i.y].id == NULL)
		return (ft_putstr_fd("Error\nCan't load texture\n", 2), 1);
	g->anim[i.x][i.y].addr = mlx_get_data_addr(g->anim[i.x][i.y].id, \
		&g->anim[i.x][i.y].bpp, &g->anim[i.x][i.y].ll, \
		&g->anim[i.x][i.y].endian);
	if (g->anim[i.x][i.y].addr == NULL)
		return (ft_putstr_fd("Error\nCan't get texture data\n", 2), 1);
	g->sprite[s].x = 0;
	g->sprite[s].y = 0;
	g->sprite[s].frame = nb_frame;
	g->sprite[s].img = &g->anim[i.x][i.y];
	g->sprite[s].ms = &g->ms;
	g->sprite[s].view = &g->view;
	if (g->sprite[s].img->height > g->sprite[s].img->width)
	{
		g->sprite[s].ry = g->sprite[s].img->height / g->sprite[s].frame;
		g->sprite[s].rx = g->sprite[s].img->width;
		g->sprite[s].axis = 0;
	}
	else
	{
		g->sprite[s].ry = g->sprite[s].img->height;
		g->sprite[s].rx = g->sprite[s].img->width / g->sprite[s].frame;
		g->sprite[s].axis = 1;
	}
	return (0); 
}
*/