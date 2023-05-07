/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:35:31 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/07 22:55:32 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
		return (1);
}

