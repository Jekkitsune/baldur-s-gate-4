/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flurry_of_blows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:41:45 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:09:41 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	atk(void *data_param, void *spell_param);
void	properties_atk(t_data *data, t_button *button, t_entity *entity,
			t_entity *weapon);

void	flurry_of_blows(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	atk(data, spell);
	spell->effect = atk;
	spell->nb = roll(spell->dice);
	spell->cost_bonus = 0;
	spell->cost_spell_slot = 0;
	if (spell->timer > 0)
		add_timer_effect(data, *spell, spell->timer, false);
}

void	init_flurry_button(t_data *data, t_button *button)
{
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = flurry_of_blows;
	button->spellinfo.type = offensive;
	button->func = action_select;
	button->spellinfo.timer = 0.5;
	button->name = "Flurry of blows";
	button->description = "Double bare hand attacks with bonus action";
	button->spellinfo.anim = "melee";
	button->img = get_tex(data, "flurry_button");
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
