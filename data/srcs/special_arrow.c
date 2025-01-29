/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:02:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:49:17 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	acid_arrow(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || !apply_action_cost(data, spell))
		return ;
	time_prop = new_timer_property(infused_acid, spell->caster, NULL, NULL);
	add_timer_property(data, time_prop, 1, true);
	show_info(data, "%s infused its arrow with acid!",
		spell->caster->sheet.name);
}

void	ensnaring_strike(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || !apply_action_cost(data, spell))
		return ;
	time_prop = new_timer_property(infused_restrained, spell->caster,
		NULL, NULL);
	add_timer_property(data, time_prop, 1, true);
	show_info(data, "%s infused its arrow with magical vines!",
		spell->caster->sheet.name);
}

void	silencing_strike(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || !apply_action_cost(data, spell))
		return ;
	time_prop = new_timer_property(infused_silenced, spell->caster,
		NULL, NULL);
	add_timer_property(data, time_prop, 1, true);
	show_info(data, "%s infused its arrow with anti-magic energy!",
		spell->caster->sheet.name);
}

void	init_more_special_arrow_button(t_data *data, t_button *button,
	t_property prop)
{
	if (prop & restrained)
	{
		button->img = get_tex(data, "ensnaring_button");
		button->spellinfo.effect = ensnaring_strike;
		button->name = "Ensnaring strike";
		button->description = "Infuse your arrow with magical vines, \
restraining your target for 2 turns!";
		return ;
	}
	if (prop & silenced)
	{
		button->spellinfo.cost_spell_slot = 2;
		button->img = get_tex(data, "silencing_button");
		button->spellinfo.effect = silencing_strike;
		button->name = "Silencing strike";
		button->description = "Infuse your arrow with anti-magic, \
silencing your target for 2 turns!";
		return ;
	}
}

void	init_special_arrow_button(t_data *data, t_button *button,
	t_property prop)
{
	button->spellinfo.range = 0;
	button->spellinfo.type = buff;
	button->spellinfo.target_self = true;
	button->spellinfo.cost_bonus = 1;
	button->func = action_select;
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->spellinfo.cost_spell_slot = 1;
	if (prop & acid)
	{
		button->img = get_tex(data, "acid_arrow_button");
		button->spellinfo.effect = acid_arrow;
		button->name = "Acid arrow";
		button->description = "Infuse your arrow with acid, reducing \
target AC by 2 for 2 turns";
		return ;
	}
	init_more_special_arrow_button(data, button, prop);
}
