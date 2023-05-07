/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:56:31 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/25 13:21:51 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief give number of char in file
 * 
 * @param pathname pathname of file
 * @return int 
 */
int	ft_file_size(char *pathname)
{
	int		fd;
	int		size;
	char	buff;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (perror("Error "), -1);
	size = 1;
	while (read(fd, &buff, 1))
		size++;
	close(fd);
	return (size);
}
