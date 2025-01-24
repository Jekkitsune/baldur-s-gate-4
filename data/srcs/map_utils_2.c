/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 02:04:15 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 09:10:48 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	has_obstacle_pos(t_data *data, t_vector from, t_vector to)
{
	float		dist;
	t_impact	ray;
	t_vectorf	true_pos1;
	t_vectorf	true_pos2;

	dist = get_dist(from, to);
	true_pos1 = vecf(from.x * (data->scale * 2) + data->scale, from.y
			* (data->scale * 2) + data->scale);
	true_pos2 = vecf(to.x * (data->scale * 2) + data->scale, to.y
			* (data->scale * 2) + data->scale);
	ray = get_simple_impact(from, vecf(true_pos2.x - true_pos1.x, true_pos2.y
				- true_pos1.y), data);
	return (get_dist(from, ray.wall_pos) < dist);
}

t_bool	is_ground(t_data *data, t_vector pos)
{
	t_cell		*cell;

	if (!in_bound(data->current_map, pos))
		return (false);
	cell = &data->current_map->arr[pos.x][pos.y];
	if (cell->type == WALL || (cell->type == DOOR && cell->status != OPEN))
		return (false);
	return (true);
}

t_bool	is_empty_cell(t_data *data, t_vector pos)
{
	t_cell		*cell;
	t_list		*entities_lst;
	t_entity	*current;

	if (!in_bound(data->current_map, pos))
		return (false);
	cell = &data->current_map->arr[pos.x][pos.y];
	if (cell->type == WALL || (cell->type == DOOR && cell->status != OPEN))
		return (false);
	entities_lst = cell->entities;
	while (entities_lst)
	{
		current = entities_lst->content;
		if (current && current->sheet.alive
			&& (current->sheet.type == living || current->sheet.type == object))
			return (false);
		entities_lst = entities_lst->next;
	}
	return (true);
}

t_map	*get_map_pointer(t_data *data, char *name)
{
	t_list	*lst;
	t_map	*current;

	lst = data->map_list;
	while (lst)
	{
		current = lst->content;
		if (current && !ft_strcmp(current->path, name))
			return (current);
		lst = lst->next;
	}
	return (NULL);
}

float	get_distf(t_vectorf p1, t_vectorf p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}
