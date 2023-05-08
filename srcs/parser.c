/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:35:31 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/08 14:32:20 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	parser_error(int errnum)
{
	if (errnum == 1)
		ft_putstr_fd("Error : cub3D only take .cub map\n", 2);
	return (errnum);
}

int	is_start(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c >= 8 && c <= 13)
		return (1);
	return (0);
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

int	extract_selector(t_texture *texture, char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		++i;
	if (line[i] == '\0')
		return (1);
	if (line[i] == 'N' && line[i + 1] == 'O')
		extract_texture(&texture->north, &line[i + 1]);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		extract_texture(&texture->south, &line[i + 1]);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		extract_texture(&texture->west, &line[i + 1]);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		extract_texture(&texture->east, &line[i + 1]);
	else if (line[i] == 'F' && is_space(line[i + 1]))
		extract_color(&texture->floor, &line[i + 1]);
	else if (line[i] == 'C' && is_space(line[i + 1]))
		extract_color(&texture->ceiling, &line[i + 1]);
	else
		return (1);
	return (0);
}

int	parser(char *pathname, t_texture *texture, t_map *map)
{
	char	*line;
	int		fd;
	int		wit;

	if (check_name(pathname))
		return (parser_error(1));
	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		return (perror("Error : "), 1);
	wit = 6;
	while (wit)
	{
		if (get_next_line(fd, line))
			return (free(line), perror("Error : "), 1);
		if (line == NULL)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		else
		{
			extract_selector(texture, line);
			free(line);
			--wit;
		}
	}
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



	
	return (0);
}
