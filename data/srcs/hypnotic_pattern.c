/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypnotic_pattern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 02:29:55 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:30:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hypnotic_pattern_zone(t_data *data, t_spellinfo *spell, t_cell *cell)
{
	t_timer_property	*time_prop;
	t_list				*lst;

	lst = cell->entities;
	if (!spell->caster)
		return ;
	while (lst)
	{
		if (lst->content && ((t_entity *)lst->content)->sheet.alive
			&& !saving_throw(data, lst->content, WIS,
			spell->caster->sheet.spell_dc))
		{
			time_prop = new_timer_property(hypnotized, lst->content,
				spell->caster, NULL);
			if (time_prop)
				time_prop->id_concentration = spell->concentration;
			add_timer_property(data, time_prop, 4, true);
		}
		lst = lst->next;
	}
}

void	hypnotic_pattern(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Hypnotic pattern!", spell->caster->sheet.name);
	zone_effect_cell(data, spell, hypnotic_pattern_zone);
}

void	init_hypnotic_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 4;
	button->spellinfo.range = 7;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.effect = hypnotic_pattern;
	button->spellinfo.type = debuff;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 3;
	button->spellinfo.concentration = 1;
	button->func = action_select;
	button->img = get_tex(data, "hypnotic_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1.5;
	button->name = "Hypnotic pattern";
	button->description = "WIS saving throw on a huge zone, if failed, cannot \
play or see until end of spell or upon taking damage";
	button->spellinfo.can_be_silenced = true;
}
