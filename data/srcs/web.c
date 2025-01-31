/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   web.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:54:00 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:35:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	web_effect(t_data *data, t_entity *entity)
{
	t_timer_property	*time_prop;

	if (!in_bound(data->current_map, entity->pos)
		|| saving_throw(data, entity, DEX, 13))
		return ;
	else
	{
		show_info(data, "%s got stuck on the web!", entity->sheet.name);
		time_prop = new_timer_property(restrained, entity, entity,
				&data->current_map->arr[entity->pos.x][entity->pos.y]);
		if (time_prop)
			time_prop->color = 0x99BBBBBB;
		add_timer_property(data, time_prop, 1, true);
	}
}

void	web_zone(t_data *data, t_spellinfo *spell, t_cell *cell)
{
	t_timer_property	*time_prop;
	t_list				*lst;

	lst = cell->entities;
	while (lst)
	{
		if (lst->content && ((t_entity *)lst->content)->sheet.alive)
			web_effect(data, lst->content);
		lst = lst->next;
	}
	time_prop = new_timer_property(webbed, NULL, spell->caster, cell);
	if (time_prop)
	{
		time_prop->color = 0x99CCCCCC;
		time_prop->id_concentration = spell->concentration;
		add_timer_property(data, time_prop, 4, true);
	}
}

void	web(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!apply_action_cost(data, spell))
		return ;
	zone_effect_cell(data, spell, web_zone);
}

void	init_web_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 3;
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = web;
	button->spellinfo.type = debuff;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->spellinfo.concentration = 1;
	button->func = action_select;
	button->img = get_tex(data, "web_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1.5;
	button->name = "Web";
	button->description = "Create a zone for 4 turns of difficult terrain, \
DEX save DD13 every turn to not get stuck, requires concentration";
	button->spellinfo.can_be_silenced = true;
}
