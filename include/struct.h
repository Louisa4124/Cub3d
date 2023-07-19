/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/07/19 12:37:14 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_game
{
	int			pause;
	int			fps_booster;
	int			color;
	int			bit_key;
	float		t;
	float		r_h;
	float		r_v;
	float		angle_z;
	float		angle_x;
	float		close_t;
	float		dist;
	t_map		map;
	t_mlx		mlx;
	t_img		view;
	t_vec3d		point;
	t_vec3d		pos;
	// t_vec3d		dir;
	t_vec2d		u_plan;
	t_vec3d		u_rays;
	t_vec3d		**rays;
	t_plan		*plan[2];
	t_plan		sky;
	t_texture	texture;
}	t_game;

#endif