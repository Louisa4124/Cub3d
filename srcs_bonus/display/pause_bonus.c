/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:50:43 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/31 21:15:09 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	load_img(t_game *game, int i, char *path)
{
	game->animation[i].id = mlx_xpm_file_to_image(game->mlx.ptr, \
		path, &game->animation[i].width, &game->animation[i].height);
	if (game->animation[i].id == NULL)
		return (ft_putstr_fd("Error\nCan't load texture\n", 2), 1);
	game->animation[i].addr = mlx_get_data_addr(game->animation[i].id, \
		&game->animation[i].bpp, &game->animation[i].ll, &game->animation[i].endian);
	if (game->button.addr == NULL)
		return (ft_putstr_fd("Error\nCan't get texture data\n", 2), 1);
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
	if (game->button.addr == NULL)
		return (ft_putstr_fd("Error\nCan't get texture data\n", 2), 1);
	return (0); 
}
