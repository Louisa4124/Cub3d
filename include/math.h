/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:35:16 by louisa            #+#    #+#             */
/*   Updated: 2023/05/07 22:58:56 by tlegrand         ###   ########.fr       */
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

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_plan
{
	float	a;
	float	b;
	float	c;
	float	d;
}	t_plan;

#endif