/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/08/04 11:12:49 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define N_THREAD 4
# define N_JOB 17
# define N_CHUNK 16

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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

typedef struct s_area
{
	int	start_x;
	int	end_x;
	int	start_y;
	int	end_y;
}	t_area;

typedef struct s_plan_id
{
	int		x;
	int		y;
	int		d;
}	t_plan_id;

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

typedef struct s_sprite
{
	t_img	*img;
	int		frame;
	// int		width_sprite;
	// int		height_sprite;
	int		x;
	int		y;
}	t_sprite;


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

typedef struct s_link
{
	t_map		*map;
	t_vec3d		*pos;
	t_plan		*plan[2];
	t_img		*view;
	int			*resolution;
	t_texture	*texture;
	t_vec3d		**rays;
	float		*angle_z;
	float		*angle_x;
	int			*mm_size;
}	t_link;

typedef struct s_tmp
{
	float		t;
	float		close_t;
	t_vec3d		point;
	t_vec3d		rays;
	t_plan_id	plan;
	int			size;
	t_vec2d		idx;
	t_link		*link;
	t_area		*area;
}	t_tmp;

typedef struct s_job
{
	int				jid;
	void			*data;
	void			*area;
	void			(*func)(void *, void *);
	struct s_job	*next;
}	t_job;

typedef struct s_game
{
	t_img		button;
    t_img       animation[31];
	t_img       anim[5][23];
	t_sprite	sprite[7];
	int			player;
	int			x;
	int			y;
    t_img       transparent;
	float		ms;
	int			pause;
    int			resolution;
	int			color;
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
	int				minimap_size;
	sem_t			sem_thread;
	sem_t			sem_main;
	t_link			link;
	t_area			area[N_CHUNK];
	pthread_t		pid[N_THREAD];
	pthread_mutex_t	m_queue;
	int				queue_status;
	t_job			**queue;
	int				n_thread;
}	t_game;



typedef struct s_thread_data
{
	int				tid;
	sem_t			*sem_main;
	sem_t			*sem_thread;
	pthread_mutex_t	*m_queue;
	int				*queue_status;
	t_job			**queue;
}	t_thread_data;


// angle less used

#endif
