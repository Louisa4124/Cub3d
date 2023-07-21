/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:50:43 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/21 22:58:31 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	load_pause(t_game *game)
{
	game->button.id = mlx_xpm_file_to_image(game->mlx.ptr, \
		"img/pause2.xpm", &game->button.width, &game->button.height);
	if (game->button.id == NULL)
		return (ft_putstr_fd("Error\nCan't load texture\n", 2), 1);
	game->button.addr = mlx_get_data_addr(game->button.id, \
		&game->button.bpp, &game->button.ll, &game->button.endian);
	if (game->button.addr == NULL)
		return (ft_putstr_fd("Error\nCan't get texture data\n", 2), 1);
	return (0); 
}
