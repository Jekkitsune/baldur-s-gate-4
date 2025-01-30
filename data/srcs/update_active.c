/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_active.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:25:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 14:09:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_spelltype_filter_color(t_data *data, t_entity *entity);
void	show_advantage(t_data *data, t_spellinfo *info);
void	ai_play(t_data *data, t_entity *current);

void	entity_filter(t_entity *entity, uint32_t color)
{
	if (!entity->color_filter)
		entity->color_filter = color;
	else
		entity->color_filter = average_filter(entity->color_filter, color);
}

void	entity_properties_effect(t_data *data, t_entity *entity)
{
	(void)data;
	if (entity->sheet.properties & hit_effect)
		entity_filter(entity, 0xFFAA0000);
	if (entity->sheet.properties & hellish_rebuke)
		entity_filter(entity, 0xFFED6111);
	if (entity->sheet.properties & enraged)
		entity_filter(entity, 0xFF550000);
	if (entity->sheet.properties & invisible)
		entity_filter(entity, 0x66000000);
	if (entity->sheet.properties & shadow_sword_prop)
		entity_filter(entity, 0xFF6B03FC);
	if (entity->sheet.properties & heal_effect)
		entity_filter(entity, 0xFF8CDE18);
	if (entity->sheet.properties & paralyzed)
		entity_filter(entity, 0xFF8A7084);
	if (entity->sheet.properties & hypnotized)
		entity_filter(entity, 0xFFF41CFF);
	if (entity->sheet.properties & hunter_marked)
		entity_filter(entity, 0xFFD94158);
	if (entity->sheet.properties & acid)
		entity_filter(entity, 0xFF8CFC03);
	if (entity->sheet.properties & silenced)
		entity_filter(entity, 0xFF6E6E6E);
}

void	radius_filter(void *data, t_entity *target,
	__attribute__((unused)) t_entity *caster, __attribute__((unused)) int nb)
{
	apply_spelltype_filter_color(data, target);
}

void	update_arrow(t_data *data)
{
	t_spellinfo	info;

	if (data->player.arrow && data->player.active_button)
	{
		info = data->player.active_button->spellinfo;
		info.pos = data->player.arrow->pos;
		info.caster = data->player.possession;
		info.target = cycle_entity_cell(data, 0);
		check_dist_obstacle(data, data->player.possession, info.range,
			info.visible_target);
		if (info.radius)
			zone_effect(data, info, radius_filter);
		else if (info.target)
		{
			apply_spelltype_filter_color(data, info.target);
			show_advantage(data, &info);
		}
		info.caster = NULL;
		info.target = NULL;
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
		// if (!current)
		// 	continue ;
		if (current->current_anim)
			continue_anim(data, current);
		update_entity_properties(data, current, false);
		entity_properties_effect(data, current);
		if (current->behavior.func && is_turn(data, current)
			&& (!current->possess_control || !data->round_manager.combat
			|| current->behavior.path))
			current->behavior.func(data, current);
		else if (data->round_manager.combat && !current->behavior.func
			&& !current->possess_control && is_turn(data, current))
			next_turn(data);
	}
}
