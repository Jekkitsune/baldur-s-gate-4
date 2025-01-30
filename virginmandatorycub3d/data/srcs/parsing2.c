/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:36 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/29 17:49:17 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_textures(t_texture *default_tex[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!default_tex[i])
			return (false);
		i++;
	}
	return (true);
}

bool	format_test(char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 5)
		return (false);
	if (name[len - 1] != 'b' || name[len - 2] != 'u' || name[len - 3] != 'c'
		|| name[len - 4] != '.')
		return (false);
	return (true);
}

void	get_lines(int fd, char *lines[7])
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(line) > 1)
		{
			lines[i] = line;
			line[ft_strlen(line) - 1] = 0;
			i += 1;
			if (i == 6)
				break ;
		}
		else
			free(line);
		line = get_next_line(fd);
	}
}

bool	check_map(t_data *data, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!check_char(map, i, j, data))
				return (free_map(map));
		}
	}
	if (vec_cmp(data->player.pos, vec(-1, -1)))
		return (free_map(map));
	if (!is_map_closed(map))
		return (free_map(map));
	return (true);
}

char	**get_map(t_data *data, int fd, t_map *level)
{
	char	*line;
	int		i;
	char	**map;

	map = NULL;
	line = get_next_line(fd);
	while (line && ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		level->size.y++;
		line[ft_strlen(line) - 1] = 0;
		map = ft_add_element_tab(map, line);
		line = get_next_line(fd);
	}
	if (!map || !check_map(data, map))
		return (NULL);
	i = -1;
	while (++i < level->size.y)
		if ((int)ft_strlen(map[i]) > level->size.x)
			level->size.x = ft_strlen(map[i]);
	return (map);
}
