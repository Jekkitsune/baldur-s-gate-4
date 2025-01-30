/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_inventory_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:40:23 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 11:57:08 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	throw(void *data_param, void *spell_param);
void	empty_button(void *data_param, void *entity_param, t_spellinfo spell);

void	consume(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;
	t_button	*action;

	data = data_param;
	spell = spell_param;
	action = &spell->summon->sheet.buttons[0];
	if (action->spellinfo.effect)
	{
		spell->nb = roll(action->spellinfo.dice);
		action->spellinfo.effect(data, spell);
	}
}

void	set_button_inventory(t_button *button, t_entity *item)
{
	if (!item)
	{
		button->spellinfo.summon = NULL;
		button->func = empty_button;
		button->spellinfo.cost_attack = 0;
		return ;
	}
	button->spellinfo.visible_target = true;
	button->func = action_select;
	button->spellinfo.type = check_type;
	if (item->sheet.type == consumable)
	{
		button->spellinfo.cost_bonus = 1;
		button->spellinfo.target_self = true;
		button->spellinfo.range = 1.5;
		button->spellinfo.effect = consume;
		button->spellinfo.summon = item;
		return ;
	}
	button->spellinfo.cost_attack = 1;
	button->spellinfo.range = ft_max(button->spellinfo.caster->sheet.stats[STR]
		/ 2, 1);
	button->spellinfo.summon = item;
	button->spellinfo.effect = throw;
}
