/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warlock_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:20:56 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 23:25:13 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_warlock_end(t_data *data, t_class *class)
{
	class->level[2].add_stats[CON] = 2;
	class->level[2].add_pv = 10;
	class->level[2].add_spell_slot[1] = 1;
	class->level[2].add_spell_slot[2] = 1;
	class->level[2].add_pb = 1;
	class->level[2].properties = seasoned_spellcaster;
	init_misty_step_button(data, &class->level[2].buttons[0]);
	init_shadow_sword_button(data, &class->level[2].buttons[1]);
	class->level[3].add_stats[WIS] = 2;
	class->level[3].add_stats[CHA] = 2;
	class->level[3].add_pv = 8;
	class->level[3].add_spell_slot[2] = 1;
	class->level[3].add_spell_slot[3] = 1;
	class->level[3].properties = true_sight;
	init_hadar_button(data, &class->level[3].buttons[0]);
	init_blight_button(data, &class->level[3].buttons[1]);
	class->level[4].add_pv = 8;
	class->level[4].add_spell_slot[1] = 1;
	class->level[4].add_pb = 1;
	class->level[4].properties = eldritch_lifesteal;
	init_banishment_button(data, &class->level[4].buttons[0]);
	add_class(&data->class_lst, class);
}

void	init_warlock_class(t_data *data)
{
	t_class	*class;

	class = ft_calloc(sizeof(t_class), 1);
	if (!class)
		return ;
	class->name = "warlock";
	class->cast_stat = CHA;
	class->level[0].add_pb = 2;
	class->level[0].add_spell_slot[0] = 2;
	init_eldritch_blast_button(data, &class->level[0].buttons[0]);
	init_hellish_rebuke_button(data, &class->level[0].buttons[1]);
	class->level[1].add_stats[DEX] = 2;
	class->level[1].add_stats[CHA] = 1;
	class->level[1].add_pv = 7;
	class->level[1].add_spell_slot[0] = 1;
	class->level[1].add_spell_slot[1] = 1;
	init_acid_puddle_button(data, &class->level[1].buttons[0]);
	init_darkness_button(data, &class->level[1].buttons[1]);
	class->level[1].properties = agonizing_blast;
	init_warlock_end(data, class);
}
