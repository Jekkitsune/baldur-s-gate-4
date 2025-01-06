/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_active.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:24:17 by fparis            #+#    #+#             */
/*   Updated: 2025/01/06 13:54:09 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_entity_properties(t_data *data, t_entity *entity)
{
	if (entity->sheet.properties & hit_effect)
		entity->color_filter = 0xFFAA0000;
}

void radius_filter(__attribute__((unused)) void *data, t_entity *target, __attribute__((unused)) t_entity *caster, __attribute__((unused)) int nb)
{
	target->color_filter = 0xFFAA0000;
}

void	update_all_active(t_data *data)
{
	t_list		*i;
	t_entity	*current;
	t_spellinfo	*info;

	if (data->player.arrow && data->player.active_button)
	{
		info = &data->player.active_button->spellinfo;
		info->pos = data->player.arrow->pos;
		info->target = cycle_entity_cell(data, 0);
		check_dist_obstacle(data, data->player.possession, info->range, info->visible_target);
		if (info->radius)
			zone_effect(data, *info, radius_filter);
		else if (info->target)
			info->target->color_filter = 0xFFAA0000;
	}
	party_follow(data);
	i = data->current_map->active_entities;
	while (i)
	{
		current = i->content;
		i = i->next;
		current->behavior.func(data, current);
		if (current->current_anim)
			continue_anim(data, current);
		update_entity_properties(data, current);
	}
}

t_bool	check_activity(t_data *data, t_entity *entity)
{
	t_list	*i;

	if (entity->active)
		return (true);
	i = data->current_map->active_entities;
	while (i)
	{
		if (i->content == entity)
		{
			entity->active = true;
			return (true);
		}
		i = i->next;
	}
	entity->active = false;
	return (false);
}

t_entity	*add_active(t_data *data, t_entity *entity, void (*behavior)(void *, void *))
{
	t_list			*new_lst;
	struct timeval 	tv;

	if (!entity)
		return (NULL);
	new_lst = ft_lstnew(entity);
	if (!new_lst)
	{
		destroy_entity(data, entity);
		return (NULL);
	}
	new_lst->content = entity;
	entity->behavior.func = behavior;
	entity->active = 1;
	gettimeofday(&tv, NULL);
	entity->behavior.start_time = tv.tv_sec;
	ft_lstadd_back(&data->current_map->active_entities, new_lst);
	return (entity);
}

void	remove_active(t_data *data, t_entity *entity)
{
	t_list	*to_free;
	
	entity->active = 0;
	if (in_bound(data->current_map, entity->pos))
	{
		if (ft_inlst(data->current_map->arr[entity->pos.x][entity->pos.y].entities, entity))
		{
			to_free = ft_lstpop(&data->current_map->active_entities, entity);
			if (to_free)
			{
				free(to_free);
				return ;
			}
		}
	}
	destroy_entity(data, entity);
}

void	destroy_active(t_data *data, t_entity *entity)
{
	t_list	*to_free;

	to_free = ft_lstpop(&data->current_map->active_entities, entity);
	if (to_free)
		free(to_free);
}
