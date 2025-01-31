/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misty_step_shadow_sword.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:08:22 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 21:40:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_shadow_sword_atk(t_data *data, t_button *button, t_entity *entity)
{
	button->spellinfo.anim = "melee";
	if (entity->sheet.class)
		button->spellinfo.stat = entity->sheet.class->cast_stat;
	else
		button->spellinfo.stat = DEX;
	button->img = get_tex(data, "shadow_sword_button");
	button->spellinfo.dice[D8] = 4;
	button->spellinfo.range = 1.5;
}

void	shadow_sword(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!apply_action_cost(data, spell))
		return ;
	time_prop = new_timer_property(shadow_sword_prop, spell->caster, NULL,
			NULL);
	add_timer_property(data, time_prop, 5, true);
	show_info(data, "%s cast Shadow sword!", spell->caster->sheet.name);
}

void	init_shadow_sword_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.effect = shadow_sword;
	button->spellinfo.type = buff;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 3;
	button->func = action_select;
	button->spellinfo.target_self = true;
	button->img = get_tex(data, "shadow_sword_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Shadow sword";
	button->description = "Replace your weapon for a melee 4d8 weapon for 5 \
turns";
	button->spellinfo.can_be_silenced = true;
}

void	misty_step(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Misty step!", spell->caster->sheet.name);
	teleport_entity(data, spell->caster, spell->pos, spell->pos_offset);
}

void	init_misty_step_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.effect = misty_step;
	button->spellinfo.type = move_type;
	button->spellinfo.cost_spell_slot = 2;
	button->spellinfo.cost_bonus = 1;
	button->func = action_select;
	button->img = get_tex(data, "misty_step_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Misty step";
	button->description = "Teleport yourself to selected position";
	button->spellinfo.can_be_silenced = true;
}
