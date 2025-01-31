/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dominate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 04:17:30 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:17:06 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dominate_effect(t_data *data, t_spellinfo *spell)
{
	t_timer_property	*time_prop;

	time_prop = new_timer_property(dominated, spell->target, spell->caster,
			NULL);
	if (!time_prop)
		return ;
	time_prop->id_concentration = spell->concentration;
	add_timer_property(data, time_prop, 10, true);
	spell->target->sheet.team = spell->caster->sheet.team;
	spell->target->behavior.was_dominated = true;
	if (spell->target->possess_control)
	{
		spell->target->behavior.dominated_player = true;
		spell->target->possess_control = false;
	}
	else if (in_party(data, spell->caster))
	{
		spell->target->possess_control = true;
		join_party(data, spell->target);
	}
}

void	dominate(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->target || spell->target->sheet.properties & dominated
		|| !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Dominate", spell->caster->sheet.name);
	if (saving_throw(data, spell->target, WIS, spell->caster->sheet.spell_dc))
		return ;
	else
		dominate_effect(data, spell);
}

void	init_dominate_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = dominate;
	button->spellinfo.type = debuff;
	button->spellinfo.concentration = 1;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 4;
	button->func = action_select;
	button->img = get_tex(data, "dominate_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Dominate";
	button->description = "Impose a WIS save throw, on failure, entity is an \
ally for 10 turns";
	button->spellinfo.can_be_silenced = true;
}
