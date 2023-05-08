/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/05/08 14:37:52 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
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
	void	*image;
	char	*addr;
	int		ll;
	int		bpp;
	int		endian;
}	t_mlx;

typedef struct s_game
{
	int		pos_x;
	int		pos_y;
	float	r_h;
	float	r_v;
	t_mlx	*mlx;
	t_vec3d	camera;
	t_vec3d	**rays;
}	t_game;

#endif