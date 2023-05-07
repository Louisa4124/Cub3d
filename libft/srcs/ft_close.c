/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:19:00 by tlegrand          #+#    #+#             */
/*   Updated: 2023/03/30 20:53:08 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_close_secure(int fd)
{
	if (fd != -1)
		if (close(fd))
			perror("Error ");
	return (-1);
}

void	ft_close_pipe(int pipefd[2])
{
	pipefd[0] = ft_close_secure(pipefd[0]);
	pipefd[1] = ft_close_secure(pipefd[1]);
}
