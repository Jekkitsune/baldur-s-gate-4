/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darkness.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:53:37 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:28:43 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	darkness_zone(t_data *data, t_spellinfo *spell, t_cell *cell)
{
	t_timer_property	*time_prop;

	time_prop = new_timer_property(blinded | invisible, NULL,
		spell->caster, cell);
	if (time_prop)
		time_prop->color = 0x99000000;
	time_prop->id_concentration = spell->concentration;
	add_timer_property(data, time_prop, 3, true);
}

void	darkness(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Darkness!", spell->caster->sheet.name);
	zone_effect_cell(data, spell, darkness_zone);
}

void	init_darkness_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 3;
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.effect = darkness;
	button->spellinfo.type = debuff;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 2;
	button->spellinfo.concentration = 1;
	button->func = action_select;
	button->img = get_tex(data, "darkness_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1.5;
	button->name = "Darkness";
	button->description = "Create a zone of darkness, creatures inside are \
invisible and blinded except with truesight, concentration needed";
	button->spellinfo.can_be_silenced = true;
}
