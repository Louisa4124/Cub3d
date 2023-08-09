/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/08/09 15:32:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"
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
# define ANG_OFFSET_MOUSE 0.003
# define RESOLUTION 2
# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_SIZE 10
# define BLUR 25
# define DEBUG	0

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

/*			Initialisation			*/
int		ft_init_game(t_game *game);
int		ft_init_mlx(t_game *game);
void	init_area_link(t_game *game);
void	init_thread_data( t_game *game, t_thread_data data[N_THREAD]);
int		load_img(t_mlx *mlx, t_img *img, char *path);
int		init_img(t_game *game);
void	fill_sprite(t_game *g, t_sprite *sprite, int nb_frame);
void	init_sprite_fill(t_game *game);
int		init_sprite(t_game *game);
void	init_igs(t_game *game, t_igs *igs);

/*			Clear					*/
void	s_mlx_destroy(t_mlx *mlx);
void	s_img_destroy(t_mlx *mlx, t_img *img);
void	s_destroy_sprite_tab(t_mlx *mlx, t_sprite *sprite, int n);
void	ft_clean_exit(t_game *game, int exit_code);

/*			Parsing					*/
int		parser(char *pathname, t_game *game);
int		parser_texture(t_mlx *mlx, t_texture *texture, int fd);
int		parser_map(t_map *map, t_game *game, int fd);

/*			Algo 				*/
int		switch_plan_algo(t_tmp *data);
int		intersect(t_tmp *data, t_plan *plan, int l_data[4], int wit);
int		intersprite(t_tmp *data, t_igs *igs, t_vec3d pos, int *color);
int		search_sprite(t_tmp *data, int *color);

/*			Color				*/
int		get_color(t_tmp *data);
int		get_color_floor(t_tmp *data, t_img floor);
int		get_color_ceiling(t_tmp *data);
int		get_color_sprite(t_igs *igs, t_vec3d point);

int		rgb_to_hexa(int r, int g, int b);
int		darken_color(int color, float d_ratio, float intensity);

/*			Move			*/
void	view_update_pos(t_game *game);
void	view_update_dir_mouse(t_game *game);
void	view_update_dir_key(t_game *game);
void	view_move(t_game *game);

/*			Display				*/
int		update_game(t_game *game);
void	ft_printf_fps(int mode);
void	ft_display_pause(t_game *game);
void	ft_display_menu(t_game *game);
void	display_game(void *ptr, void *area);
void	fredimation(void *ptr, void *area);
void	update_igs_time(t_igs *igs);
void	update_igs_plane(t_igs *igs, t_vec3d player);

/*			Events 				*/
int		event_press(int keycode, t_game *game);
int		event_unpress(int keycode, t_game *game);
int		event_mouse(int x, int y, t_game *game);
int		event_mouse_reset(t_game *game);
int		event_pause(int button, int x, int y, t_game *game);
int		close_event(t_game *game);

/*			Draw				*/
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int		extract_pixel(t_img img, int x, int y);
void	blur_image(void *ptr, void *area);
void	display_map(void *ptr, void *area);
void	draw_circle(t_img *img, t_vec2d center, int rayon, int color);
void	draw_square(t_img *img, t_vec2d center, int rayon, int color);

/*			Math utils			*/
t_vec3d	ft_rotate_vec_x(t_vec3d v, float rad);
t_vec3d	ft_rotate_vec_y(t_vec3d v, float rad);
t_vec3d	ft_rotate_vec_z(t_vec3d v, float rad);
t_vec3d	math_vec_op(t_vec3d u, t_vec3d v, char op);
t_vec3d	math_vec_k_prod(t_vec3d u, float k);
int		math_sign_float(float f);

/*			Thread & Jobs				*/
void	*routine(void *ptr);
int		add_job( t_game *game, void *data, void *area, \
	void (*func)(void *, void *));
void	clear_job(t_job **job);
int		wait_job(t_game *game);
int		send_frame_job(t_game *game);

/*			Debug				*/
void	debug_print_texture(t_texture *texture);
void	debug_print_img(t_img *img);
void	debug_print_mlx(t_mlx *mlx);
void	debug_print_map(t_map *map);
void	debug_print_vec3d(t_vec3d *u, char *name);
void	debug_print_queue(t_job *job);
void	debug_print_igs(t_igs *igs);

/*          a trier pour plus tard pck loulou a la flemme       */
int		event_menu(int x, int y, t_game *game);
int		event_settings(int x, int y, t_game *game);
int		ft_get_fps(void);

void	ft_display_menu(t_game *game);
void	ft_blur_pause(t_game *game);
void	ft_draw_img(t_img *img_dst, t_img tex, int x, int y);
int		load_menu(t_game *game, int i, int j, char *path);

void	draw_on(t_img *img_dst, t_vec2d pos, t_img img_src, t_area area);
t_img	resize_image(t_game *game, t_img *src, int ratio);
int		ft_animation_h(t_game *game, t_sprite *sprite, t_vec2d pos, \
	float speed);
void	ft_animation(t_game *game, t_sprite *sprite, t_vec2d pos);
void	animation_fire(t_game *game);
int		ft_animation_v(t_game *game, t_sprite *sprite, t_vec2d pos, float speed);
void	ft_animation_cat(t_game *game);
void	ft_settings_mouse(t_game * game, int x, int y);
void	ft_select_settings(t_game *game);
void	ft_display_settings_menu(t_game *game);
void	ft_change_cursor(t_game *game, int x, int y);

void	ft_display_menu(t_game *game);
void	ft_display_select_menu(t_game *game);
void	ft_display_select_player(t_game *game, int x, int y);
void    ft_display_players(t_game *game);
void	ft_display_fly_menu(t_game *game);
void	ft_display_launch_game(t_game *game);



int	ft_randuint(int min, int max, int *n);










#endif
