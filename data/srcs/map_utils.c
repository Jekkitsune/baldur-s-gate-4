/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:22:30 by fparis            #+#    #+#             */
/*   Updated: 2025/01/14 22:12:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	in_bound(t_map *map, t_vector vec)
{
	return ((vec.x >= 0 && vec.x < map->size.x)
		&& (vec.y >= 0 && vec.y < map->size.y));
}

int	in_window(t_vector win_size, t_vector vec)
{
	return ((vec.x >= 0 && vec.x < win_size.x)
		&& (vec.y >= 0 && vec.y < win_size.y));
}

float	get_dist(t_vector p1, t_vector p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

t_vectorf	true_pos(t_data *data, t_entity *entity)
{
	t_vectorf	res;

	res.x = (entity->pos.x) * (data->scale * 2) + (entity->offset.x + data->scale);
	res.y = (entity->pos.y) * (data->scale * 2) + (entity->offset.y + data->scale);
	return (res);
}

t_bool	has_obstacle(t_data *data, t_entity *from, t_entity *target)
{
	float		dist;
	t_impact	ray;
	t_vectorf	true_pos1;
	t_vectorf	true_pos2;

	if (!from || !target)
		return (true);
	dist = get_dist(from->pos, target->pos);
	true_pos1 = true_pos(data, from);
	true_pos2 = true_pos(data, target);
	ray = get_simple_impact(from->pos, vecf(true_pos2.x - true_pos1.x, true_pos2.y - true_pos1.y), data);
	return (get_dist(from->pos, ray.wall_pos) < dist);
}

t_bool	has_obstacle_pos(t_data *data, t_vector from, t_vector to)
{
	float		dist;
	t_impact	ray;
	t_vectorf	true_pos1;
	t_vectorf	true_pos2;

	dist = get_dist(from, to);
	true_pos1 = vecf(from.x * (data->scale * 2) + data->scale, from.y * (data->scale * 2) + data->scale);
	true_pos2 = vecf(to.x * (data->scale * 2) + data->scale, to.y * (data->scale * 2) + data->scale);
	ray = get_simple_impact(from, vecf(true_pos2.x - true_pos1.x, true_pos2.y - true_pos1.y), data);
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
		if (current && current->sheet.alive)
			return (false);
		entities_lst = entities_lst->next;
	}
	return (true);
}
