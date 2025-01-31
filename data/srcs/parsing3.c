/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/31 01:59:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_map(t_data *data, char **map, t_map *level)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!check_char(map, vec(i, j), data, level))
				return (false);
		}
	}
	if (vec_cmp(data->player.pos, vec(-1, -1)))
		return (false);
	if (!is_map_closed(map))
		return (false);
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
	if (!map || !check_map(data, map, level))
		return (NULL);
	i = -1;
	while (++i < level->size.y)
		if ((int)ft_strlen(map[i]) > level->size.x)
			level->size.x = ft_strlen(map[i]);
	return (map);
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

char	**get_map_infos(t_data *data, int fd, t_map *level)
{
	char	*lines[7];
	int		i;
	char	**map;
	bool	check;

	data->player.pos = vec(-1, -1);
	level->start = vec(-1, -1);
	i = -1;
	while (++i < 7)
		lines[i] = NULL;
	get_lines(fd, lines);
	check = process_first_infos(data, lines);
	i = -1;
	while (++i < 6)
		free(lines[i]);
	if (!check)
		return (NULL);
	map = get_map(data, fd, level);
	if (!map)
		return (NULL);
	return (map);
}

void	set_up_data(t_data *data, t_cell *cell, t_vector it, char **map)
{
	if (it.x >= (int)ft_strlen(map[it.y]))
		cell->type = VOID;
	else
		cell->type = map[it.y][it.x];
	if (cell->type == WALL || cell->type == DOOR)
	{
		cell->tex[0] = data->wall_tex[0];
		cell->tex[1] = data->wall_tex[1];
		cell->tex[2] = data->wall_tex[2];
		cell->tex[3] = data->wall_tex[3];
	}
	if (cell->type == DOOR)
	{
		cell->status = CLOSE;
		cell->timer = 1;
	}
}
