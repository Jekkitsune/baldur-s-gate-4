/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wizard_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:27:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:30:27 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_wizard_end(t_data *data, t_class *class)
{
	class->level[2].add_stats[CHA] = 2;
	class->level[2].add_pv = 5;
	class->level[2].add_pb = 1;
	class->level[2].add_spell_slot[1] = 1;
	class->level[2].add_spell_slot[2] = 1;
	class->level[2].properties = seasoned_spellcaster;
	init_trapdoor_button(data, &class->level[2].buttons[0]);
	init_group_invi_button(data, &class->level[2].buttons[1]);
	class->level[3].add_stats[INT] = 4;
	class->level[3].add_stats[WIS] = 2;
	class->level[3].add_pv = 5;
	class->level[3].add_spell_slot[2] = 1;
	class->level[3].add_spell_slot[3] = 1;
	init_hypnotic_button(data, &class->level[3].buttons[0]);
	init_dominate_button(data, &class->level[3].buttons[1]);
	class->level[4].add_pv = 5;
	class->level[4].add_pb = 1;
	class->level[4].add_spell_slot[1] = 1;
	init_fireball_button(data, &class->level[4].buttons[0]);
	class->level[4].properties = concentration_plus;
	add_class(&data->class_lst, class);
}

void	init_wizard_class(t_data *data)
{
	t_class	*class;

	class = ft_calloc(sizeof(t_class), 1);
	if (!class)
		return ;
	class->name = "wizard";
	class->cast_stat = INT;
	class->level[0].add_pb = 2;
	class->level[0].add_spell_slot[0] = 2;
	init_fire_bolt_button(data, &class->level[0].buttons[0]);
	init_healing_word_button(data, &class->level[0].buttons[1]);
	class->level[1].add_stats[INT] = 1;
	class->level[1].add_stats[WIS] = 1;
	class->level[1].add_pv = 8;
	class->level[1].add_spell_slot[0] = 1;
	class->level[1].add_spell_slot[1] = 1;
	init_web_button(data, &class->level[1].buttons[0]);
	init_hold_person_button(data, &class->level[1].buttons[1]);
	init_wizard_end(data, class);
}
