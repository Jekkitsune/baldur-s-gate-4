/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:34:20 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 15:16:29 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dash_bonus(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || !apply_action_cost(data, spell))
		return ;
	spell->caster->sheet.walked += spell->caster->sheet.speed;
	show_info(data, "%s dashed!", spell->caster->sheet.name);
}

void	init_dash_bonus_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = dash_bonus;
	button->spellinfo.type = dash_type;
	button->func = action_select;
	button->img = get_tex(data, "dash_bonus_button");
	button->name = "Dash bonus";
	button->description = "Use your action bonus to double your speed for \
the turn";
	button->spellinfo.target_self = true;
}

void	dash(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || !apply_action_cost(data, spell))
		return ;
	spell->caster->sheet.walked += spell->caster->sheet.speed;
	show_info(data, "%s dashed!", spell->caster->sheet.name);
}

void	init_dash_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.cost_action = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = dash;
	button->spellinfo.type = dash_type;
	button->func = action_select;
	button->img = get_tex(data, "dash_button");
	button->name = "Dash";
	button->description = "Use your action to double your speed for the turn";
	button->spellinfo.target_self = true;
}
