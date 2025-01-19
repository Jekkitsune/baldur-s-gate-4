#include "cub3d.h"

bool	assign_color(char **split, uint32_t *c, char color[9])
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
	*c = convert(color, "0123456789ABCDEF");
	return (true);
}

bool	create_color(char color[9], uint32_t *c, char *code)
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
	if (!assign_color(split, c, color))
		return (false);
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
			if (!create_color(data->floor_color, &data->fc, split[1]))
				return (false);
		}
		else if (split[0][0] == 'C' && data->ceiling_color[0] == 0)
		{
			if (!create_color(data->ceiling_color, &data->cc, split[1]))
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

char	**get_map_infos(t_data *data, int fd, t_map *level)
{
	char	*lines[7];
	int		i;
	char	**map;

	data->player.pos = vec(-1, -1);
	i = -1;
	while (++i < 7)
		lines[i] = NULL;
	get_lines(fd, lines);
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
