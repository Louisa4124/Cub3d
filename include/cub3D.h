/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/05/19 15:52:38 by lboudjem         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1085
# define FOV 60
# define PI 3.14159265

# define EVENT_W 119
# define EVENT_A 97
# define EVENT_S 115
# define EVENT_D 100
# define EVENT_ESC 65307

# define DARK_RED 0x8B0000
# define RED 0xff0000
# define WHITE 0xFFFFFF
# define GREEN 0x77DD77
# define BLUE 0xA7C7E7

/*          Initialisation          */
void	ft_init_game(t_game *game);
void	ft_init_rays(t_game *game);
t_vec3d	**ft_malloc_rays(t_game *game);
int		ft_init_mlx(t_game *game);

void	s_mlx_init(t_mlx *mlx);
void	s_map_init(t_map *map);
void	s_img_init(t_img *img);

/*			Clear					*/
void	s_mlx_destroy(t_game *game);
void	s_img_destroy(t_mlx *mlx, t_img *img);
void	ft_clean_exit(t_game *game, int exit_code);

/*			Parsing					*/
int		parser(char *pathname, t_game *game);
int		parser_texture(t_mlx *mlx, t_texture *texture, int fd);
int		parser_map(t_map *map, t_game *game, int fd);


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

/*			Debug					*/
void	debug_print_texture(t_texture *texture);
void	debug_print_img(t_img *img);
void	debug_print_mlx(t_mlx *mlx);
void	debug_print_map(t_map *map);

int		rgb_to_hexa(int r, int g, int b);

int		ft_update(t_game *game);
int		ft_creat_plans(t_game *game);

#endif
