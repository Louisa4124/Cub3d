/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/07/25 16:56:25 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define N_THREAD 16

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vec2d
{
	int		x;
	int		y;
}	t_vec2d;

typedef struct s_plan_data
{
	int		x;
	int		y;
	int		d;
}	t_plan_data;

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

// wall 0=N 1=S 2=W 3=E
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

typedef struct s_display
{
	int			id;
	t_map		*map;
	t_vec3d		*pos;
	t_vec3d		**rays;
	t_plan		*plan[2];
	float		*angle_z;
	float		*angle_x;
	int			idx_start;
	int			idx_end[2];
	t_img		*view;
	float		t;
	float		close_t;
	t_vec3d		tmp_point;
	t_plan_data	tmp_plan;	// vec2d -> 2 int should be an array
	t_vec3d		tmp_rays;
	t_texture	*texture;
	sem_t		*sem_thread;
	sem_t		*sem_main;
	pthread_mutex_t	*m_print;
}	t_display;

typedef struct s_game
{
	t_img		button;
	int			pause;
	int			bit_key;
	float		angle_z;
	float		angle_x;
	t_map		map;
	t_mlx		mlx;
	t_img		view;
	t_vec3d		pos;
	t_vec3d		**rays;
	t_plan		*plan[2];
	t_texture	texture;
	sem_t		sem_thread;
	sem_t		sem_main;
	pthread_t	pid[N_THREAD];
	pthread_mutex_t	m_print;
}	t_game;

// angle less used

#endif