/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:14:02 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 19:10:14 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	atk(void *data_param, void *spell_param);
void	properties_atk(t_data *data, t_button *button, t_entity *entity,
	t_entity *weapon);

void	healing_hands(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !spell->target->sheet.alive
		|| !apply_action_cost(data, spell))
		return ;
	spell->nb += modif(spell->caster->sheet.stats[WIS]);
	heal_entity(data, spell->target, spell->nb);
}

void	init_healing_hands_button(t_data *data, t_button *button)
{
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_attack = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = healing_hands;
	button->spellinfo.type = heal;
	button->spellinfo.target_self = true;
	button->func = action_select;
	button->spellinfo.timer = 0.7;
	button->name = "Healing hands";
	button->description = "Use an attack to heal an ally";
	button->spellinfo.anim = "melee";
	button->img = get_tex(data, "healing_hands_button");
	button->spellinfo.range = 1.5;
	button->spellinfo.stat = WIS;
	if (!button->user)
		return ;
	if (button->user->sheet.class)
		copy_dice(button->spellinfo.dice,
			button->user->sheet.class->level[ft_min(button->user->sheet.level
			- 1, MAX_LEVEL - 1)].current_bonus_dice);
	if (button->user->sheet.properties & healing_hand_plus)
		button->spellinfo.dice[D1] += button->user->sheet.pb;
}

void	init_bonus_punch_button(t_data *data, t_button *button)
{
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = atk;
	button->spellinfo.type = offensive;
	button->func = action_select;
	button->spellinfo.timer = 0.7;
	button->name = "Punch bonus";
	button->description = "Bare hand attack with bonus action";
	button->spellinfo.anim = "melee";
	button->img = get_tex(data, "punch_bonus_button");
	button->spellinfo.range = 1.5;
	button->spellinfo.stat = DEX;
	if (!button->user)
		return ;
	if (button->user->sheet.class)
		copy_dice(button->spellinfo.dice,
			button->user->sheet.class->level[ft_min(button->user->sheet.level
			- 1, MAX_LEVEL - 1)].current_bonus_dice);
	properties_atk(data, button, button->user, NULL);
}

void	init_monk_punch(t_button *button, t_entity *entity)
{
	button->spellinfo.stat = DEX;
	if (entity->sheet.class)
		copy_dice(button->spellinfo.dice,
			entity->sheet.class->level[ft_min(entity->sheet.level - 1,
			MAX_LEVEL - 1)].current_bonus_dice);
}
