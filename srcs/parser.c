/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:35:31 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/10 13:28:26 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	parser_error(int errnum)
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

int	parser(char *pathname, t_game *game)
{
	int		fd;

	if (check_name(pathname))
		return (parser_error(1));
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (perror("Error : "), 1);
	if (parser_texture(&game->mlx, &game->texture, fd))
		ft_clean_exit(game, EXIT_FAILURE);
	if (parser_map(&game->map, game, fd))
		ft_clean_exit(game, EXIT_FAILURE);
	
	return (0);
}

/*
	get_next_line(fd, line);
	while (line && line[0] == '\n')
	{
		free(line);
		get_next_line(fd, line);
	}
	while (line && line[0] != '\n')
	{
		extract_map(map, line);
		free(line);
		get_next_line(fd, line);
	}
*/