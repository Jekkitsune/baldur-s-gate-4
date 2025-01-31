/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/30 20:47:49 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_tex(char **split, t_data *data)
{
	if (!ft_strcmp(split[0], "NO"))
	{
		if (data->wall_tex[0])
			add_tex(data, data->wall_tex[0], ft_strdup("no"));
		data->wall_tex[0] = path_to_tex(data, split[1]);
	}
	else if (!ft_strcmp(split[0], "SO"))
	{
		if (data->wall_tex[1])
			add_tex(data, data->wall_tex[1], ft_strdup("no"));
		data->wall_tex[1] = path_to_tex(data, split[1]);
	}
	else if (!ft_strcmp(split[0], "WE"))
	{
		if (data->wall_tex[2])
			add_tex(data, data->wall_tex[2], ft_strdup("no"));
		data->wall_tex[2] = path_to_tex(data, split[1]);
	}
	else if (!ft_strcmp(split[0], "EA"))
	{
		if (data->wall_tex[3])
			add_tex(data, data->wall_tex[3], ft_strdup("no"));
		data->wall_tex[3] = path_to_tex(data, split[1]);
	}
}

bool	process_line(t_data *data, char **split)
{
	if (ft_tablen(split) != 2)
		return (false);
	if (ft_strlen(split[0]) == 1)
	{
		if (split[0][0] == 'F')
		{
			if (!create_color(data->floor_color, split[1]))
				return (false);
		}
		else if (split[0][0] == 'C')
		{
			if (!create_color(data->ceiling_color, split[1]))
				return (false);
		}
		else
			return (false);
	}
	else if (ft_strlen(split[0]) == 2)
		get_wall_tex(split, data);
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
			if (ft_inset(map[i][j], "0NSEW") && (i == 0 || j == 0
				|| i == (int) ft_tablen(map) - 1
				|| j == (int) ft_strlen(map[i]) - 1 || !map[i - 1][j]
				|| !map[i + 1][j] || !map[i][j + 1] || !map[i][j - 1]
				|| map[i - 1][j] == ' ' || map[i + 1][j] == ' '
				|| map[i][j + 1] == ' ' || map[i][j - 1] == ' '))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_char(char **map, t_vector i, t_data *data, t_map *level)
{
	if (!ft_inset(map[i.x][i.y], "012 NSEW"))
		return (false);
	if (ft_inset(map[i.x][i.y], "NSEW"))
	{
		if (!vec_cmp(level->start, vec(-1, -1)))
			return (false);
		level->start = vec(i.y, i.x);
		if (!vec_cmp(data->player.pos, vec(-1, -1)))
			return (true);
		data->player.pos = vec(i.y, i.x);
		if (map[i.x][i.y] == 'N')
			data->player.angle = M_PI + (M_PI / 2);
		else if (map[i.x][i.y] == 'S')
			data->player.angle = M_PI / 2;
		else if (map[i.x][i.y] == 'E')
			data->player.angle = 0;
		else
			data->player.angle = M_PI;
	}
	return (true);
}
