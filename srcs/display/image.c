/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjem <lboudjem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:39:15 by lboudjem          #+#    #+#             */
/*   Updated: 2023/06/30 16:51:22 by lboudjem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	blur_image(unsigned int *image_data, int width, int height)
{
    unsigned int	*temp_data;
	int				kernel_size;
	int				half_kernel;
	int				y;
	int				x;
	int				ky;
	int				kx;
	unsigned int	r_sum;
	unsigned int	g_sum;
	unsigned int	b_sum;
	unsigned int	pixel;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	r_avg;
	unsigned char	g_avg;
	unsigned char	b_avg;
	
	temp_data = (unsigned int *)malloc(width * height * sizeof(unsigned int));
    ft_memcpy(temp_data, image_data, width * height * sizeof(unsigned int));
    kernel_size = 21;
    half_kernel = kernel_size * 0.5;
	y = half_kernel;
    while (y < height) 
	{
		x = half_kernel;
        while (x < width) 
		{
            r_sum = 0;
			g_sum = 0;
			b_sum = 0;
			ky = -half_kernel;
            while (ky <= half_kernel)
			{
				kx = -half_kernel;
                while (kx <= half_kernel)
				{
                    pixel = temp_data[(y + ky) * width + (x + kx)];
                    r = (pixel >> 16) & 0xFF;
                    g = (pixel >> 8) & 0xFF;
                    b = pixel & 0xFF;
                    r_sum += r;
                    g_sum += g;
                    b_sum += b;
					++kx;
                }
				++ky;
            }
            r_avg = r_sum / (kernel_size * kernel_size);
            g_avg = g_sum / (kernel_size * kernel_size);
            b_avg = b_sum / (kernel_size * kernel_size);
            image_data[y * width + x] = (r_avg << 16) | (g_avg << 8) | b_avg;
			++x;
        }
		++y;
    }
    free(temp_data);
}