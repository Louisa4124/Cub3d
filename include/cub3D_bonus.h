/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/08/04 14:38:55 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"
# include "math.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdint.h>
# include "struct.h"

# define FOV 60
# define PI_HALF 1.570796
# define PI 3.14159265
# define PI_3_QUARTER 4.712389
# define PI_DOUBLE 6.28318531
# define PI_DIV_180 0.01745329251
# define G 9.81
# define DIR_OFFSET 0.1
# define ANG_OFFSET_KEY 0.05
# define ANG_OFFSET_MOUSE 0.03
# define RESOLUTION 2
# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_SIZE 10
# define BLUR 25
# define SEE_TH 0

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_P 112
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_SPACE 32
# define KEY_ESCAPE 65307
# define KEY_ENTER 65293

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

/*          Initialisation          */
int		ft_init_game(t_game *game);
int		ft_init_mlx(t_game *game);
void	init_area_link(t_game *game);
void	init_thread_data( t_game *game, t_thread_data data[N_THREAD]);

t_vec3d	s_vec3d_init(float x, float y, float z);
void	s_mlx_init(t_mlx *mlx);
void	s_map_init(t_map *map);
void	s_img_init(t_img *img);
void	s_texture_init(t_texture *texture);

/*			Clear					*/
void	s_mlx_destroy(t_mlx *mlx);
void	s_img_destroy(t_mlx *mlx, t_img *img);
void	ft_clean_exit(t_game *game, int exit_code);

/*			Parsing					*/
int		parser(char *pathname, t_game *game);
int		parser_texture(t_mlx *mlx, t_texture *texture, int fd);
int		parser_map(t_map *map, t_game *game, int fd);

/*			Mlx functiuns			*/
int		ft_mlx_error(int errnum, t_mlx *mlx);

int		close_event(t_game *game);
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

/*			Algo 				*/
int		k_plan_algo(t_game *game);
int		switch_plan_algo(t_tmp *data);
int		intersect(t_tmp *data, t_plan *plan, int l_data[4], int wit);

/*			Color				*/
int		get_color(t_tmp *data);
int		get_color_ceilling_floor(t_tmp *data);
int		rgb_to_hexa(int r, int g, int b);

/*			Move		*/
void	view_update_pos(t_game *game);
void	view_update_dir_mouse(t_game *game);
void	view_update_dir_key(t_game *game);

/*			Display			*/
int		update_game(t_game *game);
void	ft_printf_fps(int mode);
void	ft_display_pause(t_game *game);
void	ft_display_menu(t_game *game);
void	display_game(void *ptr, void *area);
void	fredimation(void *ptr, void *area);

/*			Events 				*/
int		event_press(int keycode, t_game *game);
int		event_unpress(int keycode, t_game *game);
void	event_mouse(int x, int y, t_game *game);
int		event_pause(int button, int x, int y, t_game *game);

/*			Draw			*/
void	blur_image(void *ptr, void *area);
void	display_map(void *ptr, void *area);
void	draw_circle(t_img *img, t_vec2d center, int rayon, int color);
void	draw_square(t_img *img, t_vec2d center, int rayon, int color);

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

/*			Thread					*/
void	*routine(void *ptr);

/*			Jobs					*/
int		add_job(t_job **head, void *data, void *area, \
	void (*func)(void *, void *));
int		send_job(t_game *game);
int		wait_job(t_game *game);

/*			Debug					*/
void	debug_print_texture(t_texture *texture);
void	debug_print_img(t_img *img);
void	debug_print_mlx(t_mlx *mlx);
void	debug_print_map(t_map *map);
void	debug_print_vec3d(t_vec3d *u, char *name);
void	debug_print_queue(t_job *job);

/*          a trier pour plus tard pck loulou a la flemme       */
int		load_img(t_game *game, t_vec2d i, char *path, int s, int nb_frame);
int		event_menu(int x, int y, t_game *game);
int		event_settings(int x, int y, t_game *game);
int		ft_get_fps(void);

void	ft_display_menu(t_game *game);
void	ft_blur_pause(t_game *game);
void    ft_draw_img(t_img *img_dst, t_img tex, int x, int y);
int		load_menu(t_game *game, int i, int j, char *path);

void	draw_on(t_img *img_dst, t_vec2d pos, t_img img_src, t_area area);
t_img	resize_image(t_game *game, t_img *src, int ratio);
int		ft_animation_h(t_game *game, t_sprite *sprite, t_vec2d pos, float speed);
void	ft_animation(t_game *game, t_sprite *sprite, t_vec2d pos);
void	animation_fire(t_game *game);

unsigned int	get_time(void);

#endif
