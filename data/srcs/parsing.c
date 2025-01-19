/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/10 11:25:40 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	parsing(int argc, char *argv[], t_data *data)
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
