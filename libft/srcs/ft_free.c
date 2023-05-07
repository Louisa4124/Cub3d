/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:56:31 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/30 18:31:13 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_free2d(void **arr, int size)
{
	int	i;

	i = -1;
	if (!arr)
		return (NULL);
	if (!size)
	{
		while (arr[++i])
			arr[i] = ft_free_secure(arr[i]);
	}
	else
	{
		while (++i < size)
			arr[i] = ft_free_secure(arr[i]);
	}
	free(arr);
	return (NULL);
}

void	*ft_free3d(void ***arr, int size3d, int *size2d)
{
	int	i;

	i = -1;
	if (!arr)
		return (NULL);
	if (!size3d)
	{
		while (arr[++i])
			arr[i] = ft_free2d(arr[i], 0);
	}
	else
	{
		if (size2d[1] == -1)
		{
			while (++i < size3d)
				arr[i] = ft_free2d(arr[i], size2d[0]);
		}
		else
		{
			while (++i < size3d)
				arr[i] = ft_free2d(arr[i], size2d[i]);
		}
	}
	free(arr);
	return (NULL);
}

void	*ft_free_secure(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
