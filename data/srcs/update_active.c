/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_active.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:25:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/22 09:21:59 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	entity_properties_effect(t_data *data, t_entity *entity)
{
	(void)data;
	if (entity->sheet.properties & hit_effect)
		entity->color_filter = 0xFFAA0000;
	if (entity->sheet.properties & poisoned)
		entity->color_filter = 0xFF00AA00;
}

void	radius_filter(__attribute__((unused)) void *data, t_entity *target,
	__attribute__((unused)) t_entity *caster, __attribute__((unused)) int nb)
{
	target->color_filter = 0xFFAA0000;
}

void	update_arrow(t_data *data)
{
	t_spellinfo	*info;

	if (data->player.arrow && data->player.active_button)
	{
		info = &data->player.active_button->spellinfo;
		info->pos = data->player.arrow->pos;
		info->target = cycle_entity_cell(data, 0);
		check_dist_obstacle(data, data->player.possession, info->range,
			info->visible_target);
		if (info->radius)
			zone_effect(data, *info, radius_filter);
		else if (info->target)
			info->target->color_filter = 0xFFAA0000;
	}
}

void	update_all_active(t_data *data)
{
	t_list		*i;
	t_entity	*current;

	party_refresh(data);
	update_arrow(data);
	party_follow(data);
	i = data->current_map->active_entities;
	while (i)
	{
		current = i->content;
		i = i->next;
		if (current->behavior.func && is_turn(data, current))
			current->behavior.func(data, current);
		else if (data->round_manager.combat && !current->behavior.func
			&& !current->possess_control && is_turn(data, current))
			next_turn(data);
		if (current->current_anim)
			continue_anim(data, current);
		update_entity_properties(data, current, false);
		entity_properties_effect(data, current);
	}
}
