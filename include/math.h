/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:35:16 by louisa            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/11 17:04:47 by lboudjem         ###   ########.fr       */
=======
/*   Updated: 2023/05/09 13:27:49 by tlegrand         ###   ########.fr       */
>>>>>>> 9b58f84b8bf55013b0b619c05c81ff1c657f589e
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

typedef struct s_vec2d
{
	float	x;
	float	y;
}	t_vec2d;

typedef struct s_line3d
{
	t_vec3d	p1;
	t_vec3d	p2;
}	t_line3d;

typedef struct s_line2d
{
	t_vec2d	p1;
	t_vec2d	p2;
}	t_line2d;

typedef struct s_plan
{
	float	a;
	float	b;
	float	c;
	float	d;
}	t_plan;

#endif