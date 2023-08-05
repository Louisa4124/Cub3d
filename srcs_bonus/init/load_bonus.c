/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:50:43 by lboudjem          #+#    #+#             */
/*   Updated: 2023/08/05 21:43:45 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	load_img(t_mlx *mlx, t_img *img, char *path)
{
	img->id = mlx_xpm_file_to_image(mlx->ptr, path, &img->width, &img->height);
	if (img->id == NULL)
		return (ft_putstr_fd("Error\nCan't load sprite\n", 2), 1);
	img->addr = mlx_get_data_addr(img->id, &img->bpp, &img->ll, &img->endian);
	if (img->addr == NULL)
		return (ft_putstr_fd("Error\nCan't get sprite data\n", 2), 1);
	return (0); 
}

void	fill_sprite(t_game *g, t_sprite *sprite, int n_frame)
{
	sprite->x = 0;
	sprite->y = 0;
	sprite->frame = n_frame;
	sprite->ms = &g->ms;
	sprite->view = &g->view;
	if (sprite->img.height > sprite->img.width)
	{
		sprite->ry = sprite->img.height / n_frame;
		sprite->rx = sprite->img.width;
		sprite->axis = 0;
	}
	else
	{
		sprite->ry = sprite->img.height;
		sprite->rx = sprite->img.width / n_frame;
		sprite->axis = 1;
	}
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
