/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/05/09 12:35:53 by lboudjem         ###   ########.fr       */
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
	int		direction;
	float	r_h;
	float	r_v;
	int		**map;
	t_mlx	mlx;
	t_plan	*plan_h;
	t_plan	*plan_v;
	t_vec3d	pos;
	t_vec3d	camera;
	t_vec3d	**rays;
}	t_game;

#endif