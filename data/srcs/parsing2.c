/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/10 11:25:40 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_tex(char **split, t_data *data)
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

bool	check_char(char **map, int i, int j, t_data *data)
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
	return (true);
}
