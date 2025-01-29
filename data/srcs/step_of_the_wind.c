/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_of_the_wind.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:07:02 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 18:15:54 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_of_the_wind(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || !apply_action_cost(data, spell))
		return ;
	spell->caster->sheet.walked += spell->caster->sheet.speed;
	time_prop = new_timer_property(dodge, spell->caster, NULL, NULL);
	add_timer_property(data, time_prop, 1, true);
	show_info(data, "%s used step of the wind!", spell->caster->sheet.name);
}

void	init_step_wind_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.effect = step_of_the_wind;
	button->spellinfo.type = move_type;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->func = action_select;
	button->img = get_tex(data, "step_wind_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Step of the wind";
	button->description = "Dash and ennemies have disadvantage on you until your \
next turn";
	button->spellinfo.cost_spell_slot = 1;
}
