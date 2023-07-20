/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:50:43 by lboudjem          #+#    #+#             */
/*   Updated: 2023/07/20 11:01:50 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	load_pause(t_game *game)
{
	t_img	pause;
	
	pause.id = mlx_xpm_file_to_image(game->mlx.ptr, "img/PlayButton.xpm", \
		 &pause.width, &pause.height);
	if (pause.id == NULL)
		return (ft_putstr_fd("Error\nCan't load texture\n", 2), 1);
	pause.addr = mlx_get_data_addr(pause.id, &pause.bpp, &pause.ll, &pause.endian);
	if (pause.addr == NULL)
		return (ft_putstr_fd("Error\nCan't get texture data\n", 2), 1);
	return (0); 
}
