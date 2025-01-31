/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_rain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:07:22 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:04:15 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	atk(void *data_param, void *spell_param);
void	properties_atk(t_data *data, t_button *button, t_entity *entity,
			t_entity *weapon);

void	arrow_rain_zone(t_data *data, t_spellinfo *spell, t_cell *cell)
{
	t_list				*lst;
	t_entity			*current;

	lst = cell->entities;
	if (!spell->caster)
		return ;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current)
		{
			spell->target = current;
			atk(data, spell);
		}
	}
}

void	arrow_rain(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || !(spell->caster->sheet.properties & range)
		|| !spell->nb || !apply_action_cost(data, spell))
		return ;
	spell->cost_bonus = 0;
	spell->cost_action = 0;
	spell->cost_spell_slot = 0;
	show_info(data, "%s cast Arrow rain!", spell->caster->sheet.name);
	zone_effect_cell(data, spell, arrow_rain_zone);
}

void	init_arrow_rain_button(t_data *data, t_button *button)
{
	t_entity	*weapon;

	button->spellinfo.radius = 2;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = arrow_rain;
	button->spellinfo.type = offensive;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 2;
	button->func = action_select;
	button->img = get_tex(data, "arrow_rain_button");
	button->spellinfo.anim = "range";
	button->spellinfo.timer = 1.5;
	button->name = "Arrow rain";
	button->description = "Range zone attack";
	if (!button->user)
		return ;
	weapon = button->user->sheet.inventory[weapon_1];
	if (!weapon || !(weapon->sheet.properties & range))
		return ;
	copy_dice(button->spellinfo.dice, weapon->sheet.dice_dmg);
	button->spellinfo.range = weapon->sheet.range;
	properties_atk(data, button, button->user, weapon);
}
