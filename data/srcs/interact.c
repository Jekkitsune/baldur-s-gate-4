/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:54:44 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 13:35:34 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_other_inventory(t_data *data)
{
	t_button	*button;

	button = data->player.active_button;
	if (!data->shown_other_inventory || !button || !button->spellinfo.caster
		|| !button->spellinfo.target || get_dist(button->spellinfo.target->pos,
			button->spellinfo.caster->pos) > 2
		|| !button->spellinfo.caster->sheet.inventory_open)
	{
		data->shown_other_inventory = false;
		data->player.shop_mode = false;
		return ;
	}
	draw_other_inventory(data, button->spellinfo.target->sheet.inventory);
}

void	open_other_inventory(t_data *data, t_button *button, t_entity *target,
		t_entity *caster)
{
	if (!button || !target || !caster)
		return ;
	remove_selector(data, false);
	data->player.active_button = button;
	button->spellinfo.target = target;
	button->spellinfo.caster = caster;
	button->spellinfo.caster->sheet.inventory_open = true;
	if (target->sheet.alive
		&& check_properties(target->sheet.properties, shop_keeper))
		data->player.shop_mode = true;
	data->shown_other_inventory = true;
}

void	interact(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (spell->target && spell->target->sheet.type == living
		&& spell->target->sheet.alive)
		talk(data_param, spell_param);
	if (spell->target && spell->target->sheet.type == living
		&& (!spell->target->sheet.alive
			|| check_properties(spell->target->sheet.properties, shop_keeper)))
		open_other_inventory(data,
			get_button_pointer(spell->caster->sheet.buttons, "Interact"),
			spell->target, spell->caster);
	else if (spell->target && spell->target->sheet.type == tavern)
		tavern_effect(data);
	else if (spell->target && (spell->target->sheet.type != living
			|| !spell->target->sheet.alive)
		&& spell->target->sheet.type != tavern)
		take(data_param, spell_param);
	else
		open_door_pos(data, spell->pos);
}

void	init_interact_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 0;
	button->spellinfo.range = 2;
	button->spellinfo.visible_target = false;
	button->spellinfo.cost_action = 0;
	button->spellinfo.type = take_type;
	button->img = get_tex(data, "take_button");
	button->func = action_select;
	button->spellinfo.effect = interact;
	button->name = "Interact";
	button->description = "Talk, open chests and doors, loot corpses, \
take objects.";
}
