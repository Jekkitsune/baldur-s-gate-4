/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2024/12/05 19:30:10 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	special_atoi(char *str, int *res)
{
	int	i;

	i = 0;
	*res = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		*res = (10 * *res) + str[i] - '0';
		i++;
	}
	return (true);
}

void	get_hexa(char hexa[2], int value)
{
	char	*base;

	base = "0123456789ABCDEF";
	hexa[0] = base[value / 16];
	hexa[1] = base[value % 16];
}

bool	create_color(char color[9], char *code)
{
	char	**split;
	int		i;
	int		value;
	char	hexa[2];

	color[0] = '0';
	color[1] = 'x';
	color[8] = 0;
	split = ft_split(code, ',');
	if (ft_tablen(split) != 3)
	{
		ft_free_tab(split);
		return (false);
	}
	i = -1;
	while (++i < 3)
	{
		if (!special_atoi(split[i], &value) || value < 0 || value > 255)
		{
			ft_free_tab(split);
			return (false);
		}
		get_hexa(hexa, value);
		color[((i + 1) * 2)] = hexa[0];
		color[((i + 1) * 2) + 1] = hexa[1];
	}
	ft_free_tab(split);
	return (true);
}

bool	process_line(t_data *data, char **split)
{
	if (ft_tablen(split) != 2)
		return (false);
	if (ft_strlen(split[0]) == 1)
	{
		if (split[0][0] == 'F' && data->floor_color[0] == 0)
		{
			if (!create_color(data->floor_color, split[1]))
				return (false);
		}
		else if (split[0][0] == 'C' && data->ceiling_color[0] == 0)
		{
			if (!create_color(data->ceiling_color, split[1]))
				return (false);
		}
		else
			return (false);
	}
	else if (ft_strlen(split[0]) == 2)
	{
		if (!ft_strcmp(split[0], "NO") && !data->wall_tex[0])
			data->wall_tex[0] = path_to_tex(data, split[1]);
		else if (!ft_strcmp(split[0], "SO") && !data->wall_tex[1])
			data->wall_tex[1] = path_to_tex(data, split[1]);
		else if (!ft_strcmp(split[0], "WE") && !data->wall_tex[2])
			data->wall_tex[2] = path_to_tex(data, split[1]);
		else if (!ft_strcmp(split[0], "EA") && !data->wall_tex[3])
			data->wall_tex[3] = path_to_tex(data, split[1]);
	}
	else
		return (false);
	return (true);
}

bool	process_first_infos(t_data *data, char *lines[7])
{
	int		i;
	char	**split;

	if (ft_tablen(lines) < 6)
		return (false);
	i = 0;
	while (i < 6)
	{
		split = ft_split(lines[i], ' ');
		if (!process_line(data, split))
		{
			ft_free_tab(split);
			return (false);
		}
		ft_free_tab(split);
		i++;
	}
	return (true);
}

bool	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_inset(map[i][j], "0NSEW") && (i == 0 || j == 0 || i == (int) ft_tablen(map) - 1
				|| j == (int) ft_strlen(map[i]) - 1 || !map[i - 1][j] || !map[i + 1][j]
				|| !map[i][j + 1] || !map[i][j - 1] || map[i - 1][j] == ' ' || map[i + 1][j] == ' '
				|| map[i][j + 1] == ' ' || map[i][j - 1] == ' '))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_map(t_data *data, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
		if (!ft_strlen(map[i]))
			return (false);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_inset(map[i][j], "012 NSEW"))
				return (false);
			if (ft_inset(map[i][j], "NSEW"))
			{
				if (!vec_cmp(data->player.pos, vec(-1, -1)))
					return (false);
				data->player.pos = vec(j, i);
				if (map[i][j] == 'N')
					data->player.angle = M_PI + (M_PI / 2);
				else if (map[i][j] == 'S')
					data->player.angle = M_PI / 2;
				else if (map[i][j] == 'E')
					data->player.angle = 0;
				else
					data->player.angle = M_PI;
			}
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
	if (!map || !check_map(data, map))
		return (NULL);
	i = -1;
	while (++i < level->size.y)
		if (ft_strlen(map[i]) > level->size.x)
			level->size.x = ft_strlen(map[i]);
	return (map);
}

char	**get_map_infos(t_data *data, int fd, t_map *level)
{
	char	*line;
	char	*lines[7];
	int		i;
	char	**map;

	data->player.pos = vec(-1, -1);
	i = -1;
	while (++i < 7)
		lines[i] = NULL;
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
	if (!process_first_infos(data, lines))
		return (NULL);
	i = -1;
	while (++i < 6)
		free(lines[i]);
	map = get_map(data, fd, level);
	if (!map)
		return (NULL);
	return (map);
}

void	turn_map(t_data *data, char **map, t_map *level)
{
	int		x;
	int		y;

	x = -1;
	while (++x < level->size.x)
	{
		y = -1;
		while (++y < level->size.y)
		{
			if (x >= ft_strlen(map[y]))
				level->arr[x][y].type = VOID;
			else
				level->arr[x][y].type = map[y][x];
			if (level->arr[x][y].type == WALL || level->arr[x][y].type == DOOR)
			{
				level->arr[x][y].tex[0] = data->wall_tex[0];
				level->arr[x][y].tex[1] = data->wall_tex[1];
				level->arr[x][y].tex[2] = data->wall_tex[2];
				level->arr[x][y].tex[3] = data->wall_tex[3];
			}
			if (level->arr[x][y].type == DOOR)
				level->arr[x][y].status = CLOSE;
		}
	}
	ft_free_tab(map);
}

bool	init_level(t_map *level)
{
	int	i;

	level->index = 0;
	level->arr = ft_calloc(level->size.x, sizeof(t_cell *));
	if (!level->arr)
		return (false);
	i = -1;
	while (++i < level->size.x)
	{
		level->arr[i] = ft_calloc(level->size.y, sizeof(t_cell));
		if (!level->arr[i])
		{
			ft_free_tab((char **)level->arr);
			return (false);
		}
	}
	i = -1;
	return (true);
}

bool	parse_map(char *path, t_data *data)
{
	int 	fd;
	t_map	*level;
	char	**map;
	t_list	*new_lst;

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
	map = get_map_infos(data, fd, level);
	if (!map)
	{
		close(fd);
		ft_putstr_fd("Error\nThe given file does not meet the requirements\n", 2);
		return (false);
	}
	close(fd);
	init_level(level);
	turn_map(data, map, level);
	if (!data->current_map)
		data->current_map = level;
	new_lst = ft_lstnew(level);
	if (!new_lst)
		exit_free(data, "Parsing malloc error");
	ft_lstadd_back(&data->map_list, new_lst);
	return (true);
}

bool	parsing(int argc, char *argv[], t_data *data)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argc == 1 || !format_test(argv[i]))
		{
			ft_putstr_fd("Error\nExpected at arguments in .cub format\n", 2);
			return (false);
		}
		if (!parse_map(argv[i], data))
			return (false);
		i++;
	}
	return (true);
}

bool	check_textures(t_texture *default_tex[4])
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!default_tex[i])
			return (false);
		i++;
	}
	return (true);
}
