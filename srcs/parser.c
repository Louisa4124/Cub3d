/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:35:31 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/08 12:59:49 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	parser_error(int errnum)
{
	if (errnum == 1)
		ft_putstr_fd("Error : cub3D only take .cub map\n", 2);
	return (errnum);
}

int	check_name(char *name)
{
	while (*name)
	{
		if (!ft_strncmp(name, ".cub", 5))
			return (0);
		++name;
	}
	return (1);
}

int	parser(char *pathname)
{
	if (check_name(pathname))
		return (parser_error(1));
	return (0);
}

