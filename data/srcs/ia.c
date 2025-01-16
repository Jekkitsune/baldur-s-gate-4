/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:55 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 23:51:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	expire(void *arg_data, void *arg_entity)
{
	t_data		*data;
	t_entity	*entity;

	data = arg_data;
	entity = arg_entity;
	if (entity->anim_loop)
		entity->anim_loop = false;
	if (entity->current_anim
		&& entity->anim_index == entity->current_anim->size - 1
		&& entity->anim_clock <= 1)
		destroy_entity(data, entity);
}

void	death(void *arg_data, void *arg_entity)
{
	t_data		*data;
	t_entity	*entity;

	data = arg_data;
	entity = arg_entity;
	if (entity->current_anim
		&& entity->anim_index == entity->current_anim->size - 1
		&& entity->anim_clock <= 1)
		destroy_active(data, entity);
}

void	move_to_center(t_data *data, t_entity *entity)
{
	t_vectorf	move;

	if (fabs(entity->offset.x) < data->player.speed && fabs(entity->offset.y)
		< data->player.speed)
	{
		move_entity(data, entity, vecf(-entity->offset.x, -entity->offset.y));
		free(pop_path(&entity->behavior.path));
		entity->sheet.walked -= 1;
		if (entity->behavior.next)
			entity->behavior.next(data, entity);
		if (!entity->behavior.path)
		{
			if (!ft_strcmp(entity->current_anim->name, "walk"))
				change_anim(entity, "idle", true);
			entity->behavior.func = entity->behavior.next;
			entity->behavior.next = NULL;
		}
		return ;
	}
	move.x = (entity->offset.x > 0) * -data->player.speed
		+ (entity->offset.x < 0) * data->player.speed;
	move.y = (entity->offset.y > 0) * -data->player.speed
		+ (entity->offset.y < 0) * data->player.speed;
	move_entity(data, entity, move);
}

void	reset_path(t_entity *entity)
{
	free_path(&entity->behavior.path);
	change_anim(entity, "idle", true);
	entity->behavior.func = entity->behavior.next;
	entity->behavior.next = NULL;
}

void	entity_moving_to(void *arg_data, void *arg_entity)
{
	t_data		*data;
	t_entity	*entity;
	t_vector	to_go;
	t_vectorf	move;

	data = arg_data;
	entity = arg_entity;
	if (!entity || !entity->behavior.path)
		return (reset_path(entity));
	if (ft_strcmp(entity->current_anim->name, "walk"))
		change_anim(entity, "walk", true);
	to_go = entity->behavior.path->pos;
	if (entity->pos.x == to_go.x
		&& entity->pos.y == to_go.y)
		return (move_to_center(data, entity));
	if ((entity->sheet.in_fight && entity->sheet.walked <= 0)
		|| !is_empty_cell(data, to_go))
		return (reset_path(entity));
	move.x = (to_go.x - entity->pos.x) * data->player.speed;
	move.y = (to_go.y - entity->pos.y) * data->player.speed;
	move_entity(data, entity, move);
	entity->angle = (move.x < 0) * M_PI + (move.y > 0) * (M_PI / 2)
		+ (move.y < 0) * (M_PI / 2 + M_PI);
}
