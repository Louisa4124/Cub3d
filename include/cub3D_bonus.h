/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/07/20 15:15:11 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"
# include "math.h"
# include "struct.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

# define FOV 60
# define PI_HALF 1.570796
# define PI 3.14159265
# define PI_3_QUARTER 4.712389
# define PI_DOUBLE 6.28318531
# define PI_DIV_180 0.01745329251
# define G 9.81
# define DIR_OFFSET 0.1
# define ANG_OFFSET_KEY 0.05
# define ANG_OFFSET_MOUSE 0.04
# define RESOLUTION 2
# define WIDTH 1080
# define HEIGHT 720
# define MINIMAP_SIZE 10

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_P 112
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define SPACE 32

# define KEY_SPACE 32
# define KEY_ESCAPE 65307

# define BFLAG_W 0b00000001
# define BFLAG_A 0b00000010
# define BFLAG_S 0b00000100
# define BFLAG_D 0b00001000
# define BFLAG_UP 0b00010000
# define BFLAG_LEFT 0b00100000
# define BFLAG_DOWN 0b01000000
# define BFLAG_RIGHT 0b100000000
# define BFLAG_P 0b1000000000

# define DARK_RED 0x8B0000
# define RED 0xff0000
# define BLACK 0x000000
# define GREY 0x808080
# define WHITE 0xFFFFFF
# define GREEN 0x77DD77
# define BLUE 0xA7C7E7

# define NO_ERR 0
# define MLX_ERR_INIT 1
# define MLX_ERR_WINDOW 2
# define MLX_ERR_IMAGE 3
# define MLX_ERR_DATA 4

/*          Initialisation          */
void	ft_init_game(t_game *game);
int		ft_init_mlx(t_game *game);
int		ft_init_airplane(t_game *game);

t_vec3d	s_vec3d_init(float x, float y, float z);
void	s_mlx_init(t_mlx *mlx);
void	s_map_init(t_map *map);
void	s_img_init(t_img *img);
void	s_texture_init(t_texture *texture);

/*			Clear					*/
void	s_mlx_destroy(t_game *game);
void	s_img_destroy(t_mlx *mlx, t_img *img);
void	ft_clean_exit(t_game *game, int exit_code);

/*			Parsing					*/
int		parser(char *pathname, t_game *game);
int		parser_texture(t_mlx *mlx, t_texture *texture, int fd);
int		parser_map(t_map *map, t_game *game, int fd);

/*			Mlx functiuns			*/
int		ft_mlx_error(int errnum);
void	ft_destroy_mlx(t_game *game);
int		close_event(t_game *game);
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

/*			Algo 				*/
int		k_plan_algo(t_game *game);
int		switch_plan_algo(t_game *game);
int		intersect(t_game *game, t_plan *plan, int u, int v, int wit);

/*			Color				*/
int		get_color(t_game *game);
int		get_color_ceilling_floor(t_game *game);
int		rgb_to_hexa(int r, int g, int b);

/*			Move		*/
void	view_update_pos(t_game *game);
void	view_update_dir_mouse(t_game *game);
void	view_update_dir_key(t_game *game);

/*			Display			*/
int		update_game(t_game *game);
void	ft_printf_fps(int mode);
void	ft_display_menu(t_game *game);

/*			Draw			*/
void	draw_map(t_game *game, int size);
void	blur_image(unsigned int *image_data, int width, int height);

/*			Events 				*/
int		event_press(int keycode, t_game *game);
int		event_unpress(int keycode, t_game *game);

/*          Math utils              */
t_vec3d	ft_rotate_vec_x(t_vec3d v, float rad);
t_vec3d	ft_rotate_vec_y(t_vec3d v, float rad);
t_vec3d	ft_rotate_vec_z(t_vec3d v, float rad);
t_vec3d	math_vec_op(t_vec3d u, t_vec3d v, char op);
t_vec3d	math_vec_k_prod(t_vec3d u, float k);
int		math_sign_float(float f);

/*			Debug					*/
void	debug_print_texture(t_texture *texture);
void	debug_print_img(t_img *img);
void	debug_print_mlx(t_mlx *mlx);
void	debug_print_map(t_map *map);
void	debug_print_vec3d(t_vec3d *u, char *name);

#endif
