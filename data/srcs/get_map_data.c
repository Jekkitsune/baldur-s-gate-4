/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 01:24:47 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 05:52:48 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_endl(char **splited);
char	**get_next_stat(int fd);
void	set_entity_map(t_data *data, char **splited);
void	get_cell_pos(char **splited_pos, t_vector *start, t_vector *end);

char	*map_param(char **splited, char *name)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		if (!ft_strcmp(splited[i], name))
			return (splited[i + 1]);
		i++;
	}
	return (NULL);
}

void	set_cell_data(t_data *data, char **splited, t_cell *cell)
{
	char		*current;
	t_texture	*tex;

	tex = get_tex(data, map_param(splited, "TEX"));
	if (tex)
	{
		cell->tex[0] = tex;
		cell->tex[1] = tex;
		cell->tex[2] = tex;
		cell->tex[3] = tex;
	}
	tex = get_tex(data, map_param(splited, "UPPER WALL"));
	if (tex)
		cell->upper_wall = tex;
	if (map_param(splited, "CEILING"))
		cell->ceiling = true;
	current = map_param(splited, "KEY");
	if (current)
		cell->key = get_prefab(data, current);
	current = map_param(splited, "TRAVEL");
	if (current)
		cell->travel = get_map_pointer(data, current);
}

void	set_cell(t_data *data, char **splited)
{
	char		*current;
	char		**tmp_splited;
	t_vector	pos;
	t_vector	end;
	int			y_start;

	current = map_param(splited, "POS");
	if (!current)
		return ;
	tmp_splited = ft_split(current, ',');
	if (!tmp_splited)
		return ;
	get_cell_pos(tmp_splited, &pos, &end);
	ft_free_tab(tmp_splited);
	y_start = pos.y;
	while (pos.x <= end.x)
	{
		pos.y = y_start;
		while (pos.y <= end.y && in_bound(data->current_map, pos))
		{
			set_cell_data(data, splited, &data->current_map->arr[pos.x][pos.y]);
			pos.y++;
		}
		pos.x++;
	}
}

void	set_map_data(t_data *data, char **splited)
{
	if (!ft_strcmp(splited[0], "CELL"))
		set_cell(data, splited);
	else if (!ft_strcmp(splited[0], "ENTITY"))
		set_entity_map(data, splited);
}

void	init_map_data(t_data *data)
{
	char	*data_file;
	int		name_len;
	int		fd;
	char	**splited;

	data_file = ft_strdup(data->current_map->path);
	if (!data_file)
		return ;
	name_len = ft_strlen(data_file);
	data_file[name_len - 3] = 'd';
	data_file[name_len - 2] = 'a';
	data_file[name_len - 1] = 't';
	fd = open(data_file, O_RDONLY);
	free(data_file);
	if (fd == -1)
		return ;
	splited = get_next_stat(fd);
	while (splited)
	{
		remove_endl(splited);
		set_map_data(data, splited);
		ft_free_tab(splited);
		splited = get_next_stat(fd);
	}
	close(fd);
}
