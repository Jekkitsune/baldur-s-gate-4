/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:22:30 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 02:04:43 by fparis           ###   ########.fr       */
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

	res.x = (entity->pos.x) * (data->scale * 2)
		+ (entity->offset.x + data->scale);
	res.y = (entity->pos.y) * (data->scale * 2)
		+ (entity->offset.y + data->scale);
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
	ray = get_simple_impact(from->pos, vecf(true_pos2.x - true_pos1.x,
				true_pos2.y - true_pos1.y), data);
	return (get_dist(from->pos, ray.wall_pos) < dist);
}
