/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/31 01:57:11 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	assign_color(char **split, char color[9])
{
	int		i;
	int		value;
	char	hexa[2];

	i = 0;
	while (i < 3)
	{
		if (!special_atoi(split[i], &value) || value < 0 || value > 255)
		{
			ft_free_tab(split);
			return (false);
		}
		get_hexa(hexa, value);
		color[((i + 1) * 2)] = hexa[0];
		color[((i + 1) * 2) + 1] = hexa[1];
		i++;
	}
	ft_free_tab(split);
	return (true);
}

bool	create_color(char color[9], char *code)
{
	char	**split;

	color[0] = '0';
	color[1] = 'x';
	color[8] = 0;
	split = ft_split(code, ',');
	if (ft_tablen(split) != 3)
	{
		ft_free_tab(split);
		return (false);
	}
	if (!assign_color(split, color))
		return (false);
	return (true);
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
			set_up_data(data, &level->arr[x][y], vec(x, y), map);
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

bool	prep_map(t_data *data, int fd, t_map *level)
{
	char	**map;

	map = get_map_infos(data, fd, level);
	if (!map)
	{
		finish_gnl(fd);
		close(fd);
		ft_putstr_fd("Error\nThe file does not meet the requirements\n", 2);
		return (false);
	}
	close(fd);
	init_level(level);
	turn_map(data, map, level);
	if (!data->current_map)
		data->current_map = level;
	return (true);
}
