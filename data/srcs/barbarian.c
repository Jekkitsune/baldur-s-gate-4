/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barbarian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:53:18 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 17:01:17 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rage(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || !apply_action_cost(data, spell))
		return ;
	if (spell->caster->sheet.properties & giant_rage)
		time_prop = new_timer_property(enraged | giant, spell->caster,
			NULL, NULL);
	else
		time_prop = new_timer_property(enraged, spell->caster, NULL, NULL);
	add_timer_property(data, time_prop, 6, true);
	show_info(data, "%s enraged!", spell->caster->sheet.name);
}

void	init_rage_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = rage;
	button->spellinfo.type = buff;
	button->spellinfo.cost_bonus = 1;
	button->func = action_select;
	button->img = get_tex(data, "rage_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Rage";
	button->description = "While enraged, only half damage received and \
stronger melee attacks";
	button->spellinfo.cost_spell_slot = 1;
	button->spellinfo.target_self = true;
}

void	reckless_attack(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || spell->caster->sheet.properties & reckless_atk)
		return ;
	time_prop = new_timer_property(reckless_atk, spell->caster, NULL, NULL);
	add_timer_property(data, time_prop, 1, true);
	show_info(data, "%s is in reckless attack!", spell->caster->sheet.name);
}

void	init_reckless_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = reckless_attack;
	button->spellinfo.type = buff;
	button->func = action_select;
	button->img = get_tex(data, "reckless_button");
	button->name = "Reckless attack";
	button->description = "Advantage on all attacks from and for you until \
your next turn";
	button->spellinfo.target_self = true;
}
