/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2024/09/19 18:23:37 by gmassoni         ###   ########.fr       */
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
		if (!ft_strcmp(split[0], "NO") && !data->textures[0])
			data->textures[0] = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "SO") && !data->textures[1])
			data->textures[1] = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "WE") && !data->textures[2])
			data->textures[2] = ft_strdup(split[1]);
		else if (!ft_strcmp(split[0], "EA") && !data->textures[3])
			data->textures[3] = ft_strdup(split[1]);
	}
	else
		return (false);
	return (true);
}

bool	process_first_infos(t_data *data, char *lines[6])
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

bool	check_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->current_map->arr[++i])
		if (!ft_strlen(data->current_map->arr[i]))
			return (false);
	i = -1;
	while (data->current_map->arr[++i])
	{
		j = -1;
		while (data->current_map->arr[i][++j])
		{
			if (!ft_inset(data->current_map->arr[i][j], "01 NSEW"))
				return (false);
			if (ft_inset(data->current_map->arr[i][j], "NSEW"))
			{
				if (!vec_cmp(data->player.pos, vec(-1, -1)))
					return (false);
				data->player.pos = vec(j, i);
				if (data->current_map->arr[i][j] == 'N')
					data->player.angle = M_PI / 2;
				else if (data->current_map->arr[i][j] == 'S')
					data->player.angle = M_PI + (M_PI / 2);
				else if (data->current_map->arr[i][j] == 'E')
					data->player.angle = 0;
				else
					data->player.angle = M_PI;
			}
		}
	}
	if (vec_cmp(data->player.pos, vec(-1, -1)))
		return (false);
	if (!is_map_closed(data->current_map->arr))
		return (false);
	return (true);
}

bool	get_map(t_data *data, int fd)
{
	char	*line;
	int		i;

	data->current_map = ft_calloc(1, sizeof(t_map));
	ft_bzero(data->current_map, sizeof(t_map));
	data->current_map->index = 0;
	line = get_next_line(fd);
	while (line && ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		data->current_map->size.y++;
		line[ft_strlen(line) - 1] = 0;
		data->current_map->arr = ft_add_element_tab(data->current_map->arr, line);
		line = get_next_line(fd);
	}
	if (!data->current_map->arr || !check_map(data))
		return (false);
	i = -1;
	while (++i < data->current_map->size.y)
		if (ft_strlen(data->current_map->arr[i]) > data->current_map->size.x)
			data->current_map->size.x = ft_strlen(data->current_map->arr[i]);
	printf("x: %i, y: %i\n", data->current_map->size.x, data->current_map->size.y);
	return (true);
}

bool	get_map_infos(t_data *data, int fd)
{
	char	*line;
	char	*lines[6];
	int		i;

	data->player.pos = vec(-1, -1);
	i = -1;
	while (++i < 6)
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
		return (false);
	i = -1;
	while (++i < 6)
		free(lines[i]);
	if (!get_map(data, fd))
		return (false);
	return (true);
}

void	turn_map(t_data *data)
{
	char	**new_map;
	size_t	size;
	size_t	size2;
	int		i;
	int		j;

	i = -1;
	size = 0;
	while (data->current_map->arr[++i])
		if (ft_strlen(data->current_map->arr[i]) > size)
			size = ft_strlen(data->current_map->arr[i]);
	new_map = ft_calloc(size + 1, sizeof(char *));
	size2 = ft_tablen(data->current_map->arr);
	i = -1;
	while (++i < size)
		new_map[i] = ft_calloc(size2 + 1, sizeof(char));
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size2)
			new_map[i][j] = data->current_map->arr[j][i];
	}
	ft_free_tab(data->current_map->arr);
	data->current_map->arr = new_map;
}

bool	parsing(int argc, char *argv[], t_data *data)
{
	int fd;

	if (argc == 1 || !format_test(argv[1]))
	{
		ft_putstr_fd("Error\nExpected at least one argument in .cub format\n", 2);
		return (false);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCannot open the given file\n", 2);
		return (false);
	}
	if (!get_map_infos(data, fd))
	{
		close(fd);
		ft_putstr_fd("Error\nThe given file does not meet the requirements\n", 2);
		return (false);
	}
	close(fd);
	turn_map(data);
	return (true);
}