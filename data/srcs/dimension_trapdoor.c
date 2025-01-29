/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimension_trapdoor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:33:38 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:30:39 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dimension_trapdoor(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (spell->target && is_empty_cell(data, spell->pos)
		&& !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Dimension trapdoor!", spell->caster->sheet.name);
	teleport_entity(data, spell->target, spell->pos, spell->pos_offset);
}

void	init_trapdoor_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.effect = dimension_trapdoor;
	button->spellinfo.type = move_type;
	button->spellinfo.cost_spell_slot = 2;
	button->spellinfo.cost_action = 1;
	button->func = man_throw_select;
	button->img = get_tex(data, "trapdoor_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Dimension trapdoor";
	button->description = "Teleport selected entity to selected position";
	button->spellinfo.can_be_silenced = true;
}
