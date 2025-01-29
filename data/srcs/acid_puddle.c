/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acid_puddle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:05:20 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:28:34 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	acid_puddle_dmg(t_data *data, t_entity *entity)
{
	int	dmg;

	dmg = roll_one(6, 2);
	if (saving_throw(data, entity, CON, 10))
		return ;
	else
		damage(data, entity, dmg);
}

void	acid_puddle_zone(t_data *data, t_spellinfo *spell, t_cell *cell)
{
	t_timer_property	*time_prop;
	t_list				*lst;

	lst = cell->entities;
	while (lst)
	{
		if (lst->content && ((t_entity *)lst->content)->sheet.alive)
			acid_puddle_dmg(data, lst->content);
		lst = lst->next;
	}
	time_prop = new_timer_property(acid_puddle_prop, NULL, spell->caster, cell);
	if (time_prop)
		time_prop->color = 0x998fd404;
	add_timer_property(data, time_prop, 3, true);
}

void	acid_puddle(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!apply_action_cost(data, spell))
		return ;
	zone_effect_cell(data, spell, acid_puddle_zone);
}

void	init_acid_puddle_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 2;
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.dice[D6] = 2;
	button->spellinfo.effect = acid_puddle;
	button->spellinfo.type = offensive;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->func = action_select;
	button->img = get_tex(data, "acid_puddle_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1.5;
	button->name = "Acid puddle";
	button->description = "2d6 on a small zone which stay 3 turns, DEX save";
	button->spellinfo.can_be_silenced = true;
}
