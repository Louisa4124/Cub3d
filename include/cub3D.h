/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/05/08 14:57:12 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"
# include "math.h"
# include "struct.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define W 800
# define H 600
# define FOV 60
# define PI 3.14159265

# define width 24
# define height 24

/*          Initialisation          */
void	ft_init_game(t_game *game);
void	ft_init_rays(t_game *game);
t_vec3d	**ft_malloc_rays(t_game *game);

/*			Mlx functiuns			*/
void	ft_destroy_mlx(t_game *game);
void	ft_clean_exit(t_game *game, int exit_code);
int		close_event(t_game *game);

/*          Math utils              */
t_vec3d	ft_rotate_vec_x(t_vec3d v, float rad);
t_vec3d	ft_rotate_vec_y(t_vec3d v, float rad);
t_vec3d	ft_rotate_vec_z(t_vec3d v, float rad);

/*          Raycasting functiuns    */
void	ft_display_game(t_game *game);

#endif
