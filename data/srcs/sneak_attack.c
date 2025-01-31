/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sneak_attack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:00:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:17:26 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sneak_atk(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;
	int			atk;
	int			rand_res;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !spell->target->sheet.alive
		|| (advantage(data, spell->caster, spell->target) < 1
			&& !is_menaced(data, spell->target, spell->caster))
		|| !apply_action_cost(data, spell))
		return ;
	rand_res = roll(spell->dice);
	spell->nb = rand_res + modif(spell->caster->sheet.stats[DEX]);
	atk = roll_atk(data, spell, spell->caster->sheet.atk_bonus
			+ modif(spell->caster->sheet.stats[DEX]));
	show_info(data, "%s use sneak attack!", spell->caster->sheet.name);
	atk_dmg(data, spell, atk, rand_res);
}

void	init_sneak_range(t_data *data, t_button *button, t_entity *weapon)
{
	button->img = get_tex(data, "sneak_range_button");
	button->spellinfo.anim = "range";
	copy_dice(button->spellinfo.dice, weapon->sheet.dice_dmg);
	add_dice(button->spellinfo.dice,
		button->user->sheet.class->level[ft_min(button->user->sheet.level - 1,
			MAX_LEVEL - 1)].current_bonus_dice);
	button->spellinfo.range = weapon->sheet.range;
}

void	init_sneak_melee(t_data *data, t_button *button, t_entity *weapon)
{
	button->spellinfo.anim = "melee";
	button->img = get_tex(data, "sneak_atk_button");
	copy_dice(button->spellinfo.dice, weapon->sheet.dice_dmg);
	add_dice(button->spellinfo.dice,
		button->user->sheet.class->level[ft_min(button->user->sheet.level - 1,
			MAX_LEVEL - 1)].current_bonus_dice);
	button->spellinfo.range = weapon->sheet.range;
}

void	init_sneak_atk_button(t_data *data, t_button *button)
{
	t_entity	*weapon;

	button->name = "Sneak attack";
	button->spellinfo.effect = sneak_atk;
	button->func = action_select;
	button->spellinfo.anim = "melee";
	button->img = get_tex(data, "sneak_atk_button");
	button->description = "Needs a finesse or range weapon";
	if (!button->user || !button->user->sheet.class)
		return ;
	weapon = button->user->sheet.inventory[weapon_1];
	if (!weapon || !(weapon->sheet.properties & (finesse | range)))
		return ;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_attack = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.type = check_type;
	button->spellinfo.timer = 0.7;
	button->description = "Strong attack on target, can only be used on targets \
on which you have advantage or if it's near an ally, need an ranged or \
finesse weapon";
	if (weapon->sheet.properties & range)
		init_sneak_range(data, button, weapon);
	else
		init_sneak_melee(data, button, weapon);
}
