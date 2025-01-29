/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warlock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:23:43 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:29:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	blight(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Blight", spell->caster->sheet.name);
	if (saving_throw(data, spell->target, CON, spell->caster->sheet.spell_dc))
		damage(data, spell->target, spell->nb / 2);
	else
		damage(data, spell->target, spell->nb);
}

void	init_blight_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = blight;
	button->spellinfo.type = offensive;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 4;
	button->func = action_select;
	button->img = get_tex(data, "blight_button");
	button->spellinfo.anim = "range";
	button->spellinfo.timer = 1;
	button->name = "Blight";
	button->spellinfo.dice[D8] = 8;
	button->description = "Impose a CON save throw to get 8d8 damage or half \
on a success";
	button->spellinfo.can_be_silenced = true;
}

void	eldritch_blast(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;
	int			atk;
	int			rand_res;

	data = data_param;
	spell = spell_param;
	if (!spell->target ||  !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Eldritch blast", spell->caster->sheet.name);
	atk = roll_atk(data, spell, spell->caster->sheet.spell_bonus);
	rand_res = spell->nb;
	atk_dmg(data, spell, atk, rand_res);
	if (spell->caster->sheet.properties & eldritch_lifesteal
		&& atk >= spell->target->sheet.ac)
		heal_entity(data, spell->caster, spell->nb / 4);
}

void	init_eldritch_blast_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = eldritch_blast;
	button->spellinfo.type = offensive;
	button->spellinfo.cost_action = 1;
	button->func = action_select;
	button->img = get_tex(data, "eldritch_button");
	button->spellinfo.anim = "range";
	button->spellinfo.timer = 1;
	button->name = "Eldritch blast";
	button->spellinfo.dice[D10] = 1;
	button->description = "1d10 spell attack";
	button->spellinfo.can_be_silenced = true;
	if (button->user && button->user->sheet.properties & agonizing_blast)
	{
		button->spellinfo.dice[D1] += modif(button->user->sheet.stats[CHA]);
		button->description = "1d10 + CHA spell attack";
	}
	if (button->user && button->user->sheet.properties & seasoned_spellcaster)
	{
		button->spellinfo.dice[D1] += modif(button->user->sheet.stats[CHA]);
		button->spellinfo.dice[D10] += 1;
		button->description = "2d10 + CHA spell attack";
	}
}
