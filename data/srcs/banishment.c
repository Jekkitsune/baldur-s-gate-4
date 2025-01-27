/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banishment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:53:42 by fparis            #+#    #+#             */
/*   Updated: 2025/01/27 02:57:05 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	banishment(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Banishment", spell->caster->sheet.name);
	if (saving_throw(data, spell->target, CHA, spell->caster->sheet.spell_dc))
		return ;
	else
	{
		time_prop = new_timer_property(banished, spell->target, spell->caster,
			NULL);
		if (time_prop)
			time_prop->id_concentration = spell->concentration;
		add_timer_property(data, time_prop, 5, true);
	}
}

void	init_banishment_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.effect = banishment;
	button->spellinfo.type = offensive;
	button->spellinfo.concentration = 1;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 4;
	button->func = action_select;
	button->img = get_tex(data, "banishment_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Banishment";
	button->description = "Impose a CHA save throw to get banished for 5 turns";
}
