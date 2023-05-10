/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/05/10 15:23:14 by lboudjem         ###   ########.fr       */
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
# define WIDTH 24
# define HEIGHT 24

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define PURPLE 0x8F00FF
# define MAROON 0x800000
# define BLACK 0x000000

/*          Initialisation          */
void	ft_init_game(t_game *game);
void	ft_init_rays(t_game *game);
t_vec3d	**ft_malloc_rays(void);
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
int		ft_inter_plan_line(t_game *game, t_plan *plan, t_vec3d *inter, int x, int y);


/*			Debug					*/
void	debug_printf_texture(t_texture *texture);
void	debug_print_img(t_img *img);
void	debug_print_mlx(t_mlx *mlx);


int		rgb_to_hexa(int r, int g, int b);

int		ft_update(t_game *game);

#endif
