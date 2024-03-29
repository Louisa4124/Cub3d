/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/10/04 11:24:40 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"
# include <X11/extensions/Xfixes.h>
# include <sys/time.h>
# include <math.h>
# include <semaphore.h>
# include <pthread.h>
# include "struct.h"

/*			constant and mode	*/
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
# define RESOLUTION 3
# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_SIZE 15
# define MINIMAP_SCALE 8
# define BLUR 25
# define FPS_MODE 0

/*			keycode and related bitflag	*/
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_P 112
# define KEY_E 101
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

/*			color code		*/
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
void	init_area(t_game *game);
void	init_link(t_game *game);
void	init_thread_data( t_game *game, t_thread_data data[N_THREAD]);
int		new_image(t_mlx *mlx, t_img *new_img, int width, int height);
int		load_img(t_mlx *mlx, t_img *img, char *path);
int		init_img(t_game *game);
void	fill_sprite(t_game *g, t_sprite *sprite, int nb_frame);
int		init_igs(t_game *game, t_igs *igs);
void	set_mlx_hook(t_game *game);

/*			Clear					*/
void	s_mlx_destroy(t_mlx *mlx);
void	s_img_destroy(t_mlx *mlx, t_img *img);
void	ft_clean_exit(t_game *game, int exit_code);

/*			Parsing					*/
int		parser(char *pathname, t_game *game);
int		parser_texture(t_mlx *mlx, t_texture *texture, int fd);
int		parser_map(t_map *map, t_game *game, int fd);
int		parser_doors(t_game *game);

/*			Algo 				*/
int		switch_plan_algo(t_tmp *data);
int		intersect(t_tmp *data, t_plan plan, t_vec3d pos, int coord[2]);
int		interdoor(t_tmp *data, t_door *door, t_vec3d pos);
int		intersprite(t_tmp *data, t_igs *igs, t_vec3d pos, int wit);
int		update_game(t_game *game);
void	update_igs_time(t_igs *igs);
void	update_igs_plane(t_igs *igs, t_vec3d player);
int		is_near_door(t_game *game, t_door *doors, t_vec3d *pos);
void	update_doors_dist(t_door *doors, t_vec3d *pos, int n_doors);
void	update_door(t_game *game);

/*			Color				*/
int		get_color(t_tmp *data, t_map *map, t_vec3d *pos);
int		get_color_floor(t_tmp *data, t_img floor);
int		get_color_sprite(t_igs *igs, t_vec3d point);
int		get_color_ceiling(t_tmp *data, t_img ceiling);
int		get_color_door(t_door *door, t_vec3d point);
int		rgb_to_hexa(int r, int g, int b);
int		darken_color(int color, float d_ratio, float intensity);

/*			Move			*/
void	view_update_pos(t_game *game);
void	view_update_dir_key(t_game *game);
void	update_door_status(t_game *game);

/*			Display				*/
void	display_game(void *ptr, void *area);
void	ft_display_menu(t_game *game);
void	ft_settings_mouse(t_game *game);
void	ft_select_settings(t_game *game);
void	ft_display_settings_menu(t_game *game);
void	ft_change_cursor(t_game *game, int x, int y);
void	ft_display_menu(t_game *game);
void	ft_display_select_menu(t_game *game);
void	ft_display_select_player(t_game *game, int x, int y);
void	ft_display_players(t_game *game);
void	ft_display_fly_menu(t_game *game);
void	ft_display_launch_game(t_game *game);
void	ft_display_settings(t_game *game);
int		ft_animation_h(t_game *game, t_sprite *sprite, t_vec2d pos, \
	float speed);
void	ft_animation(t_game *game, t_sprite *sprite, t_vec2d pos);
void	animation_fire(t_game *game);
int		ft_animation_v(t_game *game, t_sprite *sprite, t_vec2d pos, \
	float speed);
void	ft_animation_cat(t_game *game, float speed);

/*			Events 				*/
int		event_press(int keycode, t_game *game);
int		event_unpress(int keycode, t_game *game);
int		event_mouse(int x, int y, t_game *game);
int		event_mouse_reset(t_game *game);
int		event_pause(int button, int x, int y, t_game *game);
int		close_event(t_game *game);
void	event_resolution(int x, int y, t_game *game);
void	event_sensitivity(int x, int y, t_game *game);
void	event_luminosity(int x, int y, t_game *game);
void	pause_off(t_game *game);
int		event_menu(int x, int y, t_game *game);
int		event_settings(int x, int y, t_game *game);
int		ft_in_wall(t_map *map, int x, int y);
void	ft_jump(t_game *game);

/*			Draw				*/
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int		extract_pixel(t_img img, int x, int y);
void	blur_image(void *ptr, void *area);
void	display_map(void *ptr, void *area);
void	draw_circle(t_img *img, t_vec2d center, int rayon, int color);
void	draw_square(t_img *img, t_vec2d center, int rayon, int color);
void	ft_draw_img(t_img *img_dst, t_img tex, int x, int y);
void	ft_draw_img_vel(t_img *img_dst, t_img tex, float x, float y);
void	draw_on(t_img *img_dst, t_vec2d pos, t_img img_src, t_area area);
int		resize_image(t_game *game, t_img *src, int ratio);
void	ft_blur_pause(t_game *game);
void	draw_map(t_link *ln, t_vec2d *idx_map, t_vec2d	*idx_draw, void *area);

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
int		launch_thread(t_game *game, t_thread_data th[N_THREAD]);

/*			Utils				*/
int		ft_randuint(int min, int max, int *n);
int		is_near(t_vec3d p1, t_vec3d p2, float e);
int		better_mlx_mouse_hide(void *xvar, void *win, int *cursor);
int		better_mlx_mouse_show(void *xvar, void *win, int *cursor);
int		ft_get_fps(void);
void	ft_printf_fps(int mode);

#endif
