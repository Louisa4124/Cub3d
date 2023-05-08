/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/05/08 15:17:09 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	int		direction;
	float	r_h;
	float	r_v;
	int		**map;
	t_mlx	mlx;
	t_plan	*plan_h;
	t_plan	*plan_v;
	t_vec3d	**rays;
	t_vec3d	camera;
}	t_game;

#endif