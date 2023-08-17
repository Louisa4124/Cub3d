/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/08/17 20:34:04 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define N_THREAD 4
# define N_CHUNK 16
# define N_SPRITE 20
# define N_IGS 2

typedef void	(*t_job_func)(void *, void *);

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
	t_img	img;
	int		frame;
	int		x;
	int		y;
	int		rx;
	int		ry;
	int		axis;
	float	*ms;
	t_img	*view;
}	t_sprite;

typedef struct s_igs
{
	t_sprite	*sp;
	t_plan		plan;
	t_vec3d		pos;
	float		t;
	float		ms;
}	t_igs;

typedef struct s_texture
{
	t_img	wall[5];
	t_img	t_floor;
	t_img	t_ceiling;
	t_img	t_door;
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
	t_igs		*igs;
	float		*light;
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
	t_img		*img;
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
	t_img			anim[5][23];
	t_sprite		sprite[N_SPRITE];
	t_area			area[N_CHUNK];
	t_texture		texture;
	t_link			link;
	t_img			view;
	t_img			blur;
	pthread_mutex_t	m_queue;
	pthread_t		pid[N_THREAD];
	t_igs			igs[N_IGS];
	sem_t			sem_thread;
	sem_t			sem_main;
	t_mlx			mlx;
	t_map			map;
	t_plan			*plan[2];
	t_vec3d			pos;
	t_vec3d			**rays;
	t_vec2d			mouse;
	t_job			**queue;
	float			light;
	int				jump;
	int				pause;
	int				player;
	int				resolution;
	int				bit_key;
	float			ms;
	float			angle_z;
	float			angle_x;
	float			angle_offset;
	float			sensitivity;
	int				n_job;
	int				n_thread;
	int				minimap_size;
	int				queue_status;
	int				debug;
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

#endif
