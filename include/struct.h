/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/05/11 17:22:40 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img
{
	void	*id;
	char	*addr;
	int		*data;
	int		height;
	int		width;
	int		ll;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
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
}	t_mlx;

typedef struct s_game
{
	float		r_h;
	float		r_v;
	float		angle_z;
	float		angle_x;
	int			**map;
	//t_map		map;
	t_img		img_n;
	t_img		img_s;
	t_img		img_w;
	t_img		img_e;
	t_mlx		mlx;
	t_img		view;
	t_vec3d		pos;
	t_vec3d		dir;
	t_vec3d		camera;
	t_vec3d		**rays;
	t_plan		*plan[2];
	t_texture	texture;
}	t_game;

#endif