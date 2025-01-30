/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:56:27 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/29 17:39:39 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	finish_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

bool	free_map(char **map)
{
	ft_free_tab(map);
	return (false);
}

bool	prep_map(t_data *data, int fd, t_map *level)
{
	char	**map;

	map = get_map_infos(data, fd, level);
	if (!map)
	{
		finish_gnl(fd);
		close(fd);
		free(level->path);
		free(level);
		ft_putstr_fd("Error\nThe file does not meet the requirements\n", 2);
		return (false);
	}
	close(fd);
	init_level(level);
	turn_map(data, map, level);
	if (!data->map)
		data->map = level;
	return (true);
}

bool	parse_map(char *path, t_data *data)
{
	int		fd;
	t_map	*level;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCannot open the given file\n", 2);
		return (false);
	}
	level = ft_calloc(sizeof(t_map), 1);
	if (!level)
		return (false);
	level->path = ft_calloc(ft_strlen(path), sizeof(char));
	if (level->path)
		ft_strlcpy(level->path, path, ft_strlen(path));
	if (!prep_map(data, fd, level))
		return (false);
	return (true);
}

bool	parsing(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (argc != 2 || !format_test(argv[i]))
	{
		ft_putstr_fd("Error\nExpected one argument in .cub format\n", 2);
		return (false);
	}
	while (i < argc)
	{
		if (!parse_map(argv[i], data))
			return (false);
		i++;
	}
	return (true);
}
