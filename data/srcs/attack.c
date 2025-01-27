/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 05:02:33 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 19:51:11 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_shadow_sword_atk(t_data *data, t_button *button, t_entity *entity);

void	properties_atk(t_data *data, t_button *button, t_entity *entity,
	t_entity *weapon)
{
	if (!data)
		return ;
	if (entity->sheet.properties & giant
		&& (!weapon || !(weapon->sheet.properties & range)))
	{
		button->spellinfo.range += 1;
		button->spellinfo.dice[D8] += 1;
	}
}

void	atk(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;
	int			atk;
	int			rand_res;

	data = data_param;
	spell = spell_param;
	if (!spell->target || spell->target == spell->caster
		|| !spell->target->sheet.alive || !apply_action_cost(data, spell))
		return ;
	rand_res = roll(spell->dice);
	spell->nb = rand_res + modif(spell->caster->sheet.stats[spell->stat]);
	if (spell->caster->sheet.properties & enraged)
		spell->nb += class_bonus_dmg(spell->caster);
	atk = roll_atk(data, spell, spell->caster->sheet.atk_bonus);
	atk_dmg(data, spell, atk, rand_res);
}

void	init_range(t_data *data, t_button *button, t_entity *weapon)
{
	button->spellinfo.stat = DEX;
	button->img = get_tex(data, "range_button");
	button->spellinfo.anim = "range";
	copy_dice(button->spellinfo.dice, weapon->sheet.dice_dmg);
	button->spellinfo.range = weapon->sheet.range;
}

void	init_melee(t_data *data, t_button *button, t_entity *entity,
	t_entity *weapon)
{
	button->spellinfo.anim = "melee";
	button->spellinfo.stat = STR;
	if (weapon && (weapon->sheet.properties & finesse))
		button->spellinfo.stat = DEX;
	if (!weapon)
	{
		if (has_dice(entity->sheet.dice_dmg))
			copy_dice(button->spellinfo.dice, entity->sheet.dice_dmg);
		else
			set_dice(button->spellinfo.dice, D1, 1);
		button->spellinfo.range = 1.5;
		button->img = get_tex(data, "punch_button");
		return ;
	}
	button->img = get_tex(data, "melee_button");
	copy_dice(button->spellinfo.dice, weapon->sheet.dice_dmg);
	button->spellinfo.range = weapon->sheet.range;
}

void	init_atk_button(t_data *data, t_button *button, t_entity *entity)
{
	t_entity	*weapon;

	weapon = entity->sheet.inventory[weapon_1];
	button->spellinfo.radius = 0;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_attack = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = atk;
	button->spellinfo.type = offensive;
	button->func = action_select;
	button->spellinfo.timer = 0.7;
	button->name = "Attack";
	button->description = "Attack selected with the equipped weapon";
	if (entity->sheet.properties & shadow_sword_prop)
		init_shadow_sword_atk(data, button, entity);
	else if (weapon && weapon->sheet.properties & range)
		init_range(data, button, weapon);
	else
		init_melee(data, button, entity, weapon);
	properties_atk(data, button, entity, weapon);
}
