/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/08/05 19:25:39 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define FOV 60
# define PI_HALF 1.570796
# define PI 3.14159265
# define PI_3_QUARTER 4.712389
# define PI_DOUBLE 6.28318531
# define PI_DIV_180 0.01745329251
# define DIR_OFFSET 0.1
# define ANG_OFFSET_KEY 0.05
# define RESOLUTION 2
# define WIDTH 800
# define HEIGHT 600

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_P 112
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESCAPE 65307

# define BFLAG_W 0b00000001
# define BFLAG_A 0b00000010
# define BFLAG_S 0b00000100
# define BFLAG_D 0b00001000
# define BFLAG_LEFT 0b00100000
# define BFLAG_RIGHT 0b100000000

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

typedef struct s_vec2d
{
	int		x;
	int		y;
}	t_vec2d;

typedef struct s_plan
{
	float	a;
	float	b;
	float	c;
	float	d;
}	t_plan;

typedef struct s_img
{
	void	*id;
	char	*addr;
	int		height;
	int		width;
	int		ll;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	wall[4];
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_map
{
	int	**layout;
	int	x_size;
	int	y_size;
}	t_map;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	int		win_height;
	int		win_width;
}	t_mlx;

typedef struct s_game
{
	t_img			button;
	int				x;
	int				y;
	t_vec3d			point;
	t_vec3d			u_rays;
	t_vec2d			u_plan;
	int				color;
	float			t;
	float			close_t;
	int				bit_key;
	float			r_v;
	float			r_h;
	float			angle_z;
	float			angle_x;
	float			angle_offset;
	t_map			map;
	t_mlx			mlx;
	t_img			view;
	t_vec3d			pos;
	t_vec3d			**rays;
	t_plan			*plan[2];
	t_texture		texture;
}	t_game;

/*			Initialisation			*/
int		ft_init_mlx(t_game *game);
int		ft_init_game(t_game *game);

/*			Parsing					*/
int		parser(char *pathname, t_game *game);
int		parser_texture(t_mlx *mlx, t_texture *texture, int fd);
int		parser_map(t_map *map, t_game *game, int fd);

/*			Events 				*/
int		event_press(int keycode, t_game *game);
int		event_unpress(int keycode, t_game *game);
int		close_event(t_game *game);

/*			Algo 				*/
void	ft_switch_plan(t_game *game);

/*			Color				*/
void	get_color(t_game *game);
void	get_color_ceiling_floor(t_game *game);
int		rgb_to_hexa(int r, int g, int b);

/*			Move		*/
void	view_update_pos(t_game *game);
void	view_update_dir(t_game *game);

/*			Display			*/
int		update_game(t_game *game);
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

/*			Math utils			*/
t_vec3d	ft_rotate_vec_x(t_vec3d v, float rad);
t_vec3d	ft_rotate_vec_y(t_vec3d v, float rad);
t_vec3d	ft_rotate_vec_z(t_vec3d v, float rad);
t_vec3d	math_vec_op(t_vec3d u, t_vec3d v, char op);
t_vec3d	math_vec_k_prod(t_vec3d u, float k);
int		math_sign_float(float f);

/*			Clear					*/
void	s_mlx_destroy(t_mlx *mlx);
void	s_img_destroy(t_mlx *mlx, t_img *img);
void	ft_clean_exit(t_game *game, int exit_code);

/*			Debug					*/
void	debug_print_texture(t_texture *texture);
void	debug_print_img(t_img *img);
void	debug_print_mlx(t_mlx *mlx);
void	debug_print_map(t_map *map);
void	debug_print_vec3d(t_vec3d *u, char *name);
void	ft_printf_fps(void);

#endif
