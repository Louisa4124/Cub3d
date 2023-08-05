/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:50:43 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/05 13:29:38 by lboudjem         ###   ########.fr       */
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
