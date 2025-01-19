/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:45:40 by fparis            #+#    #+#             */
/*   Updated: 2025/01/17 01:46:54 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_entity(t_data *data, t_entity *entity, t_vectorf move)
{
	t_vector	l_pos;
	t_list		*entity_lst;
	t_map		*map;

	map = data->current_map;
	l_pos = entity->pos;
	entity->offset.x += move.x;
	entity->offset.y += move.y;
	correct_pos(data, &entity->pos, &entity->offset);
	if (entity->pos.x != l_pos.x || entity->pos.y != l_pos.y)
	{
		if (in_bound(map, l_pos))
		{
			entity_lst = ft_lstpop(&map->arr[l_pos.x][l_pos.y].\
			entities, entity);
			if (entity_lst && in_bound(map, entity->pos))
			{
				entity_lst->next = NULL;
				ft_lstadd_back(&map->arr[entity->pos.x][entity->pos.y].entities,
					entity_lst);
				return ;
			}
		}
		destroy_entity(data, entity);
	}
}

void	move_to(t_data *data, t_entity *entity, t_vector pos)
{
	if (!entity)
		return ;
	if (entity->behavior.path)
		free_path(&entity->behavior.path);
	entity->behavior.path = get_path(data, entity->pos, pos, false);
	if (!entity->behavior.path)
	{
		printf("%s: \"BAH NON DCP\"\n", entity->sheet.name);
		return ;
	}
	entity->behavior.next = entity->behavior.func;
	if (!entity->active)
		add_active(data, entity, entity_moving_to);
	else
		entity->behavior.func = entity_moving_to;
}

void	move_closest_to(t_data *data, t_entity *entity, t_entity *target)
{
	if (entity->behavior.path)
		free_path(&entity->behavior.path);
	entity->behavior.path = get_path(data, entity->pos, target->pos, true);
	if (!entity->behavior.path)
	{
		printf("%s: \"can't go near\"\n", entity->sheet.name);
		return ;
	}
	entity->behavior.next = entity->behavior.func;
	entity->behavior.func = entity_moving_to;
}

void	teleport_entity(t_data *data, t_entity *entity, t_vector pos,
	t_vectorf offset)
{
	t_vector	l_pos;
	t_list		*entity_lst;

	l_pos = entity->pos;
	entity->pos = pos;
	entity->offset = offset;
	correct_pos(data, &entity->pos, &entity->offset);
	if (entity->pos.x != l_pos.x || entity->pos.y != l_pos.y)
	{
		if (in_bound(data->current_map, l_pos))
		{
			entity_lst = ft_lstpop(&data->current_map->arr[l_pos.x][l_pos.y].\
				entities, entity);
			if (entity_lst && in_bound(data->current_map, entity->pos))
			{
				entity_lst->next = NULL;
				ft_lstadd_back(&data->current_map->\
					arr[entity->pos.x][entity->pos.y].entities, entity_lst);
				return ;
			}
			free(entity_lst);
		}
		destroy_entity(data, entity);
	}
}
