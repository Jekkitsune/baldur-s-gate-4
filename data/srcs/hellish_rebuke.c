/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellish_rebuke.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:52:07 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 17:01:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hellish_rebuke_effect(t_data *data, t_entity *caster, t_entity *hitter)
{
	int	dmg;

	if (!remove_specific_prop(data, caster, hellish_rebuke))
		return ;
	show_info(data, "%s proc %s's hellish rebuke!", hitter->sheet.name,
		caster->sheet.name);
	dmg = roll_one(10, 2);
	if (saving_throw(data, hitter, DEX, caster->sheet.spell_dc))
		damage(data, hitter, dmg / 2);
	else
		damage(data, hitter, dmg);
}

void	hellish_rebuke_cast(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || spell->caster->sheet.properties & hellish_rebuke
		|| !apply_action_cost(data, spell))
		return ;
	time_prop = new_timer_property(hellish_rebuke, spell->caster, NULL, NULL);
	add_timer_property(data, time_prop, 10, true);
	show_info(data, "%s cast Hellish rebuke", spell->caster->sheet.name);
}

void	init_hellish_rebuke_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.target_self = true;
	button->spellinfo.effect = hellish_rebuke_cast;
	button->spellinfo.type = buff;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->func = action_select;
	button->img = get_tex(data, "hellish_rebuke_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1.5;
	button->name = "Hellish rebuke";
	button->spellinfo.dice[D10] = 2;
	button->description = "When hit by an opponent, impose a DEX saving, for \
2d10 damage or half on success";
}
