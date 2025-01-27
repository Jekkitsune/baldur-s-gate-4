/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hold_person.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:29:49 by fparis            #+#    #+#             */
/*   Updated: 2025/01/27 02:56:46 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hold_person(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Hold person!", spell->caster->sheet.name);
	if (saving_throw(data, spell->target, WIS, spell->caster->sheet.spell_dc))
		return ;
	else
	{
		time_prop = new_timer_property(paralyzed, spell->target, spell->caster,
			NULL);
		if (time_prop)
			time_prop->id_concentration = spell->concentration;
		add_timer_property(data, time_prop, 5, true);
	}
}

void	init_hold_person_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = hold_person;
	button->spellinfo.type = debuff;
	button->spellinfo.concentration = 1;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 2;
	button->func = action_select;
	button->img = get_tex(data, "hold_person_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Hold person";
	button->description = "Impose a WIS save throw to not get paralyze for \
5 turns, a successful melee attack on paralyzed entity crits";
}
