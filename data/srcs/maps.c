/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:58:54 by fparis            #+#    #+#             */
/*   Updated: 2024/08/23 23:11:50 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	get_map_size(char *path)
{
	int			fd;
	t_vector	size;
	char		buf[1];
	int			tmp_x;

	size.x = 0;
	size.y = 0;
	tmp_x = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (size);
	size.y++;
	while (read(fd, buf, 1))
	{
		tmp_x++;
		if (buf[0] == '\n')
		{
			size.y++;
			size.x = ft_max(size.x, tmp_x - 1);
			tmp_x = 0;
		}
	}
	close(fd);
	return (size);
}

void	*fill_map(t_map *map, char *path)
{
	int		fd;
	char	*line;
	int		i;
	int		i2;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i2 = 0;
		while (line[i2] && i2 < map->size.x)
		{
			if ((line[i2] == '1' || line[i2] == '0'))
			{
				//printf("i:%d, i2:%d\n", i, i2);
				map->arr[i2][i] = line[i2];
			}
			i2++;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (map);
}

void	print_map(t_map *map)
{
	int	i;
	int i2;

	i = 0;
	while (i < map->size.y)
	{
		i2 = 0;
		while (i2 < map->size.x)
		{
			if (map->arr[i2][i])
				printf("%c", map->arr[i2][i]);
			else
				printf(" ");
			i2++;
		}
		printf("\n");
		i++;
	}
}

t_map	*create_map(char *path)
{
	t_map	*map;
	int		i;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (NULL);
	map->size = get_map_size(path);
	map->arr = ft_calloc(sizeof(char *), map->size.x);
	i = 0;
	while (i < map->size.x)
	{
		map->arr[i] = ft_calloc(sizeof(char), map->size.y);
		i++;
	}
	fill_map(map, path);
	return (map);
}
