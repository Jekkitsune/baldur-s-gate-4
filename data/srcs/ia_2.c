/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:48:49 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 10:54:34 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_pos_speed(t_vectorf *offset, float angle, float speed)
{
	t_vectorf	direc;

	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	direc.x = cosf(angle);
	direc.y = sinf(angle);
	offset->x += direc.x * speed;
	offset->y += direc.y * speed;
}

void	move_projectile(t_data *data, t_entity *entity, t_vectorf pos,
		t_vectorf target_pos)
{
	float		dist;
	t_vectorf	new_offset;
	double		angle;

	dist = get_distf(pos, target_pos);
	if (dist < data->player.speed * 2)
	{
		entity->behavior.spell.effect(data, &entity->behavior.spell.effect);
		destroy_entity(data, entity);
		return ;
	}
	new_offset = entity->offset;
	angle = atan2(target_pos.y - pos.y, target_pos.x - pos.x);
	change_pos_speed(&new_offset, angle, data->player.speed * 2);
	teleport_entity(data, entity, entity->pos, new_offset);
}

void	projectile_ia(void *data_param, void *entity_param)
{
	t_data		*data;
	t_entity	*entity;
	t_entity	*target;
	t_vectorf	proj_pos;
	t_vectorf	target_pos;

	data = data_param;
	entity = entity_param;
	target = entity->behavior.target;
	if (!target || !entity->behavior.spell.effect)
	{
		destroy_entity(data, entity);
		return ;
	}
	proj_pos.x = (entity->pos.x) * (data->scale * 2)
		+ (entity->offset.x + data->scale);
	proj_pos.y = (entity->pos.y) * (data->scale * 2)
		+ (entity->offset.y + data->scale);
	target_pos.x = (target->pos.x) * (data->scale * 2)
		+ (target->offset.x + data->scale);
	target_pos.y = (target->pos.y) * (data->scale * 2)
		+ (target->offset.y + data->scale);
	move_projectile(data, entity, proj_pos, target_pos);
}
