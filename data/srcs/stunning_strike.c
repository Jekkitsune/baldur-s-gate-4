/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stunning_strike.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:31:25 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:15:42 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	atk(void *data_param, void *spell_param);
void	properties_atk(t_data *data, t_button *button, t_entity *entity,
			t_entity *weapon);

void	stunning_strike(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !spell->caster)
		return ;
	show_info(data, "%s used stunning strike!", spell->caster->sheet.name);
	atk(data, spell);
	if (saving_throw(data, spell->target, CON, spell->caster->sheet.spell_dc))
		return ;
	else
	{
		show_info(data, "%s is stunned!", spell->target->sheet.name);
		time_prop = new_timer_property(stunned, spell->target, NULL, NULL);
		add_timer_property(data, time_prop, 1, true);
	}
}

void	init_stunning_strike_button(t_data *data, t_button *button)
{
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = stunning_strike;
	button->spellinfo.type = offensive;
	button->func = action_select;
	button->spellinfo.timer = 0.5;
	button->name = "Stunning strike";
	button->description = "Bare hand attack, CON save on target to not get \
stunned";
	button->spellinfo.anim = "melee";
	button->img = get_tex(data, "stunning_strike_button");
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
