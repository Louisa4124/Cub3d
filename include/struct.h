/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/05/08 11:37:36 by lboudjem         ###   ########.fr       */
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
	float	r_h;
	float	r_v;
	t_mlx	*mlx;
	t_vec3d	camera;
	t_vec3d	**rays;
}	t_game;

#endif