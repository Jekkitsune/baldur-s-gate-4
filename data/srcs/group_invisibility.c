/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_invisibility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:46:24 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:30:47 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	group_invisibility(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;
	t_list				*lst;

	data = data_param;
	spell = spell_param;
	if (!apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Group invisibility!", spell->caster->sheet.name);
	lst = data->round_manager.party;
	while (lst)
	{
		if (lst->content)
		{
			time_prop = new_timer_property(invisible, lst->content,
				spell->caster, NULL);
			if (time_prop)
				time_prop->id_concentration = spell->concentration;
			add_timer_property(data, time_prop, 10, true);
		}
		lst = lst->next;
	}
}

void	init_group_invi_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = group_invisibility;
	button->spellinfo.type = check_type;
	button->spellinfo.cost_action = 1;
	button->spellinfo.cost_spell_slot = 3;
	button->spellinfo.concentration = 1;
	button->func = action_select;
	button->img = get_tex(data, "group_invi_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Group invisibility";
	button->description = "Make the whole party invisible, you have advantage \
	while invisible and ennemies cannot engage combat and in combat, can't see \
	you if more than 1 cell away, requires concentration";
	button->spellinfo.target_self = true;
	button->spellinfo.can_be_silenced = true;
}
