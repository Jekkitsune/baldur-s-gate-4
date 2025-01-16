/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_draw_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:41:58 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 21:43:13 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_obj_x(t_data *data, t_vectorf pos, t_vectorf p_pos)
{
	float	obj_angle;
	float	angle_diff;
	float	x;

	obj_angle = atan2(p_pos.y - pos.y, pos.x - p_pos.x);
	angle_diff = -obj_angle - data->player.angle;
	if (fabs(angle_diff) > M_PI)
		angle_diff = ((2 * M_PI) - angle_diff) * -1;
	if (fabs(fabs(fmod(angle_diff, 2 * M_PI)) - M_PI) < M_PI / 2)
		return (data->win_size.x);
	x = tan(angle_diff) * (WIDTH / 2) + (WIDTH / 2);
	return (x);
}

float	get_obj_y(t_data *data, t_vectorf true_pos, t_vectorf p_pos,
	t_vector *i)
{
	float	slope;
	float	size;
	float	distance;

	slope = data->player.camera_plane.y / data->player.camera_plane.x;
	slope = tan(angle_add(data->player.angle, -(M_PI / 2)));
	distance = fabs(((p_pos.y - true_pos.y) * -1) - (slope * \
	(true_pos.x - p_pos.x))) / sqrt(slope * slope + 1.0);
	size = (data->win_size.y / (distance / (data->scale * 2)));
	i->x = (data->win_size.y / 2) - (size / 2);
	i->y = (data->win_size.y / 2) + (size / 2);
	i->x += data->player.pitch + (data->player.height / distance);
	i->y += data->player.pitch + (data->player.height / distance);
	return (distance);
}

void	calculate_entity_info(t_data *data, t_entity *entity)
{
	t_vectorf	p_pos;

	entity->true_pos.x = (entity->pos.x) * (data->scale * 2)
		+ (entity->offset.x + data->scale);
	entity->true_pos.y = (entity->pos.y) * (data->scale * 2)
		+ (entity->offset.y + data->scale);
	p_pos.x = data->player.pos.x * (data->scale * 2)
		+ (data->player.offset.x + data->scale);
	p_pos.y = data->player.pos.y * (data->scale * 2)
		+ (data->player.offset.y + data->scale);
	entity->draw_x.x = get_obj_x(data, entity->true_pos, p_pos);
	entity->distance = get_obj_y(data, entity->true_pos, p_pos,
			&entity->draw_y);
	entity->draw_y.x -= (entity->draw_y.y - entity->draw_y.x)
		* (entity->size_scale - 1);
	if (entity->draw_x.x == data->win_size.x)
		return ;
	entity->draw_x.y = (WIDTH / entity->distance * (data->scale * 2))
		* entity->size_scale;
	entity->draw_x.x = entity->draw_x.x - (entity->draw_x.y / 2);
	entity->draw_x.y = entity->draw_x.x + entity->draw_x.y;
}
