/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consumable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:45:29 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 12:59:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_consumable(t_data *data, t_entity *user, t_entity *used)
{
	int	i;

	if (!user || !used)
		return ;
	i = 0;
	while (i < INVENTORY_SIZE)
	{
		if (user->sheet.inventory[i] == used)
		{
			destroy_entity(data, used);
			user->sheet.inventory[i] = NULL;
		}
		i++;
	}
}

int	get_inventory_item_i(t_entity *user, t_entity *used)
{
	int	i;

	if (!user || !used)
		return (-1);
	i = 0;
	while (i < INVENTORY_SIZE)
	{
		if (user->sheet.inventory[i] == used)
			return (i);
		i++;
	}
	return (-1);
}

void	heal_potion(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->summon || !spell->target || spell->target->sheet.type != living
		|| !apply_action_cost(data, spell))
		return ;
	heal_entity(data, spell->target, spell->nb);
	destroy_consumable(data, spell->caster, spell->summon);
}

void	init_heal_potion_button(t_data *data, t_button *button)
{
	if (!data)
		return ;
	button->spellinfo.radius = 0;
	button->spellinfo.range = 1.5;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.type = check_type;
	button->func = action_select;
	button->spellinfo.effect = heal_potion;
	button->name = "Healing potion";
	button->spellinfo.dice[D6] = 2;
	button->description = "Heal target 2D6 hp";
}

void	init_greater_heal_potion_button(t_data *data, t_button *button)
{
	if (!data)
		return ;
	button->spellinfo.radius = 0;
	button->spellinfo.range = 1.5;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.type = check_type;
	button->func = action_select;
	button->spellinfo.effect = heal_potion;
	button->name = "Greater healing potion";
	button->spellinfo.dice[D6] = 4;
	button->description = "Heal target 4D6 hp";
}
