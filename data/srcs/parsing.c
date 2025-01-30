/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:09:45 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/29 14:29:23 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_map(char *path, t_data *data)
{
	int		fd;
	t_map	*level;
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
	new_lst = ft_lstnew(level);
	if (!new_lst)
	{
		free(level);
		exit_free(data, "Parsing malloc error");
	}
	ft_lstadd_back(&data->map_list, new_lst);
	level->path = ft_strdup(path);
	if (!prep_map(data, fd, level))
		return (false);
	return (true);
}

bool	parsing(int argc, char *argv[], t_data *data)
{
	int	i;

	i = 1;
	if (argc == 1)
	{
		ft_putstr_fd("Error\nExpected at arguments in .cub format\n", 2);
		return (false);
	}
	while (i < argc)
	{
		if (!format_test(argv[i]) || !parse_map(argv[i], data))
			return (false);
		i++;
	}
	return (true);
}
