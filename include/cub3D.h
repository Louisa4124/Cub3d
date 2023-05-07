/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisa <louisa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:38:36 by louisa            #+#    #+#             */
/*   Updated: 2023/05/07 22:16:32 by louisa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"
# include "../math.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define W 800
# define H 600
# define FOV 60
# define PI 3.14159265
# define r_h 2 * tan(FOV / 2) / W
# define r_v 2 * tan(FOV * H / (W * 2)) / H

typedef struct s_game
{
	int     pos_x;
    int     pos_y;
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
<<<<<<< HEAD
}				t_mlx;
=======
}	t_mlx;
>>>>>>> f1de1bf1e0d3126b76ad886f3e71c5711e47fc59

#endif

/*
typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;

*/