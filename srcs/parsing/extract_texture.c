/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:24:08 by tlegrand          #+#    #+#             */
/*   Updated: 2023/05/22 11:18:05 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	extract_texture(t_mlx *mlx, t_img *img, char *path)
{
	int	i;

	while (*path && ft_isspace(*path))
		++path;
	if (*path == '\0')
		return (ft_putstr_fd("Error\nCan't find texture\n", 2), 1);
	i = 0;
	while (path[i] && path[i] != '\n')
		++i;
	path[i] = '\0';
	img->id = mlx_xpm_file_to_image(mlx->ptr, path, &img->width, &img->height);
	if (img->id == NULL)
		return (ft_putstr_fd("Error\nCan't load texture\n", 2), 1);
	img->addr = mlx_get_data_addr(img->id, &img->bpp, &img->ll, &img->endian);
	if (img->addr == NULL)
		return (ft_putstr_fd("Error\nCan't get texture data\n", 2), 1);
	return (0);
}

static int	extract_color(int *color, char *line)
{
	int	rgb[3];
	int	i;

	while (*line && ft_isspace(*line))
		++line;
	i = 0;
	while (i < 3)
	{
		if (ft_isdigit(*line))
			rgb[i] = ft_atoi(line) % 256;
		else
			break ;
		if (rgb[i] < 0)
			break ;
		while (*line && ft_isdigit(*line))
			++line;
		if (*line == ',')
			++line;
		++i;
	}
	if (i < 3)
		return (ft_putstr_fd("Error\nWrong rgb color\n", 2), 1);
	*color = rgb_to_hexa(rgb[0], rgb[1], rgb[2]);
	return (0);
}

static int	extract_selector(t_mlx *mlx, t_texture *texture, char *line)
{
	int		i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		++i;
	if (line[i] == '\0')
		return (2);
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (extract_texture(mlx, &texture->wall[0], &line[i + 2]));
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (extract_texture(mlx, &texture->wall[1], &line[i + 2]));
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (extract_texture(mlx, &texture->wall[2], &line[i + 2]));
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (extract_texture(mlx, &texture->wall[3], &line[i + 2]));
	if (line[i] == 'F')
		return (extract_color(&texture->floor, &line[i + 1]));
	if (line[i] == 'C')
		return (extract_color(&texture->ceiling, &line[i + 1]));
	ft_putstr_fd("Error\nUnexpected line while parsing\n", 2);
	return (1);
}

static int	all_texture(t_texture *texture)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (texture->wall[i].id == NULL)
			return (1);
		++i;
	}
	return (0);
}

int	parser_texture(t_mlx *mlx, t_texture *texture, int fd)
{
	char	*line;
	int		count;
	int		wit;

	count = 6;
	line = NULL;
	while (count)
	{
		if (get_next_line(fd, &line))
			return (perror("Error\n "), 1);
		if (line == NULL)
			break ;
		wit = extract_selector(mlx, texture, line);
		if (wit == 1)
			return (ft_free_secure(line), 1);
		else if (wit == 0)
			--count;
		line = ft_free_secure(line);
	}
	if (count || all_texture(texture))
		ft_putstr_fd("Error\nData about color or texture missing\n", 2);
	return (count);
}
