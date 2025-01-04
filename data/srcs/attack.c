/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 05:02:33 by fparis            #+#    #+#             */
/*   Updated: 2025/01/04 06:48:13 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	atk(void *data_param, void *spell_param)
{
	t_data 		*data;
	t_spellinfo	*spell;
	int			atk;

	data = data_param;
	spell = spell_param;
	spell->nb = roll(spell->dice) + modif(spell->caster->sheet.stats[spell->stat]);
	atk = roll_one(20, 1) + spell->caster->sheet.atk_bonus;
	if (atk >= spell->target->sheet.ac)
	{
		show_info(data, "%s hit (%d) %s (%d)", spell->caster->sheet.name, atk, spell->target->sheet.name, spell->target->sheet.ac);
		damage(data, spell->target, spell->nb);
	}
	else
		show_info(data, "%s missed (%d) %s (%d)", spell->caster->sheet.name, atk, spell->target->sheet.name, spell->target->sheet.ac);
}

void	init_range(t_data *data, t_button *button, t_entity *entity, t_entity *weapon)
{
	button->spellinfo.stat = DEX;
	button->img = get_tex(data, "range_button");
	button->spellinfo.anim = "range";
	copy_dice(button->spellinfo.dice, weapon->sheet.dice_dmg);
	button->spellinfo.range = weapon->sheet.range;
}

void	init_atk_button(t_data *data, t_button *button, t_entity *entity)
{
	t_entity	*weapon;

	weapon = entity->sheet.inventory[weapon_1];
	button->spellinfo.radius = 0;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = atk;
	button->func = action_select;
	button->spellinfo.timer = 1;
	button->spellinfo.name = "Attack";
	if (weapon && weapon->sheet.properties & range)
		return (init_range(data, button, entity, weapon));
	button->img = get_tex(data, "melee_button");
	button->spellinfo.anim = "melee";
	button->spellinfo.stat = STR;
	if (weapon && weapon->sheet.properties & finesse)
		button->spellinfo.stat = DEX;
	if (!weapon)
	{
		set_dice(button->spellinfo.dice, D1, 1);
		button->spellinfo.range = 1;
		return ;
	}
	copy_dice(button->spellinfo.dice, weapon->sheet.dice_dmg);
	button->spellinfo.range = weapon->sheet.range;
}
