/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:50:43 by lboudjem          #+#    #+#             */
/*   Updated: 2023/09/05 00:24:31 by tlegrand         ###   ########.fr       */
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

void	fill_all_sprite(t_game *game)
{
	fill_sprite(game, &game->sprite[0], 8);
	fill_sprite(game, &game->sprite[1], 10);
	fill_sprite(game, &game->sprite[2], 5);
	fill_sprite(game, &game->sprite[3], 6);
	fill_sprite(game, &game->sprite[4], 6);
	fill_sprite(game, &game->sprite[5], 6);
	fill_sprite(game, &game->sprite[6], 6);
	fill_sprite(game, &game->sprite[7], 8);
	fill_sprite(game, &game->sprite[8], 8);
	fill_sprite(game, &game->sprite[9], 8);
	fill_sprite(game, &game->sprite[10], 19);
	fill_sprite(game, &game->sprite[11], 10);
	fill_sprite(game, &game->sprite[12], 8);
	fill_sprite(game, &game->sprite[13], 5);
	fill_sprite(game, &game->sprite[14], 13);
	fill_sprite(game, &game->sprite[15], 8);
	fill_sprite(game, &game->sprite[16], 1);
	fill_sprite(game, &game->sprite[18], 19);
}
