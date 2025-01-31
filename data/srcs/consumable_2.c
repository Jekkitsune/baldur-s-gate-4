/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consumable_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:59:22 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:06:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_consumable(t_data *data, t_entity *user, t_entity *used);

void	enlarge_potion(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->summon || !spell->target || spell->target->sheet.type != living
		|| !apply_action_cost(data, spell))
		return ;
	time_prop = new_timer_property(giant, spell->target, NULL, NULL);
	add_timer_property(data, time_prop, 3, true);
	show_info(data, "%s drank a potion of enlargement!",
		spell->target->sheet.name);
	destroy_consumable(data, spell->target, spell->summon);
}

void	init_enlarge_potion_button(t_data *data, t_button *button)
{
	if (!data)
		return ;
	button->spellinfo.radius = 0;
	button->spellinfo.range = 1.5;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.type = check_type;
	button->func = action_select;
	button->spellinfo.effect = enlarge_potion;
	button->name = "Enlarge potion";
	button->description = "Enlarge target for 3 turns, \
in this state, regains deals 1D8 dmg bonus and has more melee \
range actions per turn";
}

void	speed_potion(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->summon || !spell->target || spell->target->sheet.type != living
		|| !apply_action_cost(data, spell))
		return ;
	time_prop = new_timer_property(haste, spell->target, NULL, NULL);
	add_timer_property(data, time_prop, 3, true);
	show_info(data, "%s drank a potion of speed!", spell->target->sheet.name);
	destroy_consumable(data, spell->target, spell->summon);
	spell->target->sheet.action++;
}

void	init_speed_potion_button(t_data *data, t_button *button)
{
	if (!data)
		return ;
	button->spellinfo.radius = 0;
	button->spellinfo.range = 1.5;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.type = check_type;
	button->func = action_select;
	button->spellinfo.effect = speed_potion;
	button->name = "Speed potion";
	button->description = "Grant haste effect to target for 3 turns, \
in this state, regains 2 actions per turn";
}
