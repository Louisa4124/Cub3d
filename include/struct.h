/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:12:42 by louisa            #+#    #+#             */
/*   Updated: 2023/05/07 23:13:25 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_game
{
	int     pos_x;
    int     pos_y;
    float   r_h;
    float   r_v;
    t_vec3d rays;
    t_vec3d camera;
}	t_game;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*image;
	char	*addr;
	int		line_length;
	int		bits_per_pixel;
	int		endian;
}	t_mlx;

#endif