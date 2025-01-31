/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hunger_of_hadar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:58:58 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:32:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hunger_of_hadar_dmg(t_data *data, t_entity *entity)
{
	int	dmg;

	dmg = roll_one(6, 4);
	if (saving_throw(data, entity, DEX, 16))
		return ;
	else
		damage(data, entity, dmg);
}

void	hunger_of_hadar_zone(t_data *data, t_spellinfo *spell, t_cell *cell)
{
	t_timer_property	*time_prop;
	t_list				*lst;

	lst = cell->entities;
	while (lst)
	{
		if (lst->content && ((t_entity *)lst->content)->sheet.alive)
			hunger_of_hadar_dmg(data, lst->content);
		lst = lst->next;
	}
	time_prop = new_timer_property(blinded | hunger_of_hadar_prop
			| difficult_terrain, NULL,
			spell->caster, cell);
	if (time_prop)
		time_prop->color = 0x9921006E;
	time_prop->id_concentration = spell->concentration;
	add_timer_property(data, time_prop, 4, true);
}

void	hunger_of_hadar(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Hunger of Hadar!", spell->caster->sheet.name);
	zone_effect_cell(data, spell, hunger_of_hadar_zone);
}

void	init_hadar_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 3;
	button->spellinfo.range = 5;
	button->spellinfo.visible_target = true;
	button->spellinfo.target_self = true;
	button->spellinfo.effect = hunger_of_hadar;
	button->spellinfo.type = offensive;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 3;
	button->spellinfo.concentration = 1;
	button->func = action_select;
	button->img = get_tex(data, "hadar_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1.5;
	button->name = "Hunger of hadar";
	button->description = "Create a zone of evil darkness, it's a difficult \
terrain and creatures inside are \
invisible and blinded except with truesight, all creatures must succeed a DEX \
save or get 4D6 damage concentration needed";
	button->spellinfo.can_be_silenced = true;
}
