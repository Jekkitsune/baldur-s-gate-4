#include "cub3d.h"

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
	if (!ft_inset(map[i][j], "01 NSEW"))
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

void	set_up_data(t_data *data, t_cell *cell, t_vector it, char **map)
{
	if (it.x >= (int)ft_strlen(map[it.y]))
		cell->type = VOID;
	else
		cell->type = map[it.y][it.x];
	if (cell->type == WALL)
	{
		cell->tex[0] = data->wall_tex[0];
		cell->tex[1] = data->wall_tex[1];
		cell->tex[2] = data->wall_tex[2];
		cell->tex[3] = data->wall_tex[3];
	}
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
