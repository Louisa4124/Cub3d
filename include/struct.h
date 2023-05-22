/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/05/22 11:08:52 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_imgs
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_imgs;

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
	float		r_h;
	float		r_v;
	float		angle_z;
	float		angle_x;
	t_map		map;
	t_mlx		mlx;
	t_img		view;
	t_vec3d		pos;
	t_vec3d		dir;
	t_vec3d		camera;
	t_vec3d		**rays;
	t_plan		**plan;
	t_texture	texture;
}	t_game;

#endif