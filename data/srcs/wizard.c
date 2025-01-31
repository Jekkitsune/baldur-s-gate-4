/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wizard.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:29:59 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 09:41:23 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	healing_word(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Healing word", spell->caster->sheet.name);
	heal_entity(data, spell->target, spell->nb);
}

void	init_healing_word_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = healing_word;
	button->spellinfo.type = heal;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->spellinfo.target_self = true;
	button->func = action_select;
	button->img = get_tex(data, "healing_word_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Healing word";
	button->spellinfo.dice[D4] = 2;
	button->description = "Heals target 2d4 + spellcasting stat modifier";
	if (!button->user)
		return ;
	if (button->user->sheet.class && button->user->sheet.class->cast_stat)
		button->spellinfo.dice[D1] += modif(button->user->sheet.\
		stats[button->user->sheet.class->cast_stat]);
	if (button->user->sheet.properties & seasoned_spellcaster)
	{
		button->spellinfo.dice[1] += button->user->sheet.spell_bonus;
		button->description = "Heals target 2d4 + spell attack bonus + \
spellcasting stat modifier";
	}
}

void	fire_bolt(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;
	int			atk;
	int			rand_res;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Fire bolt", spell->caster->sheet.name);
	atk = roll_atk(data, spell, spell->caster->sheet.spell_bonus);
	rand_res = spell->nb;
	atk_dmg(data, spell, atk, rand_res);
}

void	init_fire_bolt_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 6.5;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = fire_bolt;
	button->spellinfo.type = offensive;
	button->spellinfo.cost_action = 1;
	button->func = action_select;
	button->img = get_tex(data, "fire_bolt_button");
	button->spellinfo.anim = "range";
	button->spellinfo.timer = 1;
	button->name = "Fire bolt";
	button->spellinfo.dice[D10] = 1;
	button->description = "1d10 spell attack";
	if (!button->user)
		return ;
	if (button->user->sheet.properties & seasoned_spellcaster)
	{
		button->spellinfo.dice[D10] += 1;
		button->description = "2d10 + CHA spell attack";
	}
	button->spellinfo.can_be_silenced = true;
}
