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

void	get_hexa(char hexa[2], int value)
{
	char	*base;

	base = "0123456789ABCDEF";
	hexa[0] = base[value / 16];
	hexa[1] = base[value % 16];
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

int	get_index(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

uint32_t	convert(char *color, char *base)
{
	uint32_t	result;
	int			i;

	result = 0;
	i = 2;
	while (color[i])
	{
		result = result * 16 + get_index(base, color[i]);
		i++;
	}
	return (result + 0xFF000000);
}
