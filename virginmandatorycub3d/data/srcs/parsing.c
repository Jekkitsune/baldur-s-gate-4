#include "cub3d.h"

bool	prep_map(t_data *data, int fd, t_map *level)
{
	char	**map;

	map = get_map_infos(data, fd, level);
	if (!map)
	{
		close(fd);
		ft_putstr_fd("Error\nThe file does not meet the requirements\n", 2);
		return (false);
	}
	close(fd);
	init_level(level);
	turn_map(data, map, level);
	if (!data->map)
		data->map = level;
	return (true);
}

bool	parse_map(char *path, t_data *data)
{
	int		fd;
	t_map	*level;

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
	if (!prep_map(data, fd, level))
		return (false);
	return (true);
}

bool	parsing(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	if (argc == 1 || !format_test(argv[i]))
	{
		ft_putstr_fd("Error\nExpected at arguments in .cub format\n", 2);
		return (false);
	}
	while (i < argc)
	{
		if (!parse_map(argv[i], data))
			return (false);
		i++;
	}
	return (true);
}
