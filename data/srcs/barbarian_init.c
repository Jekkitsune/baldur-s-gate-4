/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barbarian_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:04:44 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 13:51:27 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_barbarian_class_2(t_data *data, t_class *class)
{
	class->level[2].add_pb = 1;
	class->level[2].add_pv = 10;
	class->level[2].add_stats[DEX] = 1;
	class->level[2].add_nb_attack = 1;
	class->level[3].current_bonus_dice[D1] = 3;
	class->level[3].add_stats[STR] = 2;
	class->level[3].add_stats[CON] = 2;
	class->level[3].add_spell_slot[0] = 1;
	class->level[3].add_pv = 14;
	class->level[3].current_bonus_dice[D1] = 4;
	init_man_throw_button(data, &class->level[3].buttons[0]);
	class->level[4].add_stats[INT] = -1;
	class->level[4].add_stats[CHA] = 1;
	class->level[4].add_pv = 11;
	class->level[4].add_pb = 1;
	class->level[4].properties = giant_rage;
	class->level[4].current_bonus_dice[D1] = 5;
	add_class(&data->class_lst, class);
}

void	init_barbarian_class(t_data *data)
{
	t_class	*class;

	class = ft_calloc(sizeof(t_class), 1);
	if (!class)
		return ;
	class->name = "barbarian";
	class->level[0].add_pb = 2;
	class->level[0].add_spell_slot[0] = 1;
	class->level[0].current_bonus_dice[D1] = 2;
	class->level[0].properties = unarmored_defense;
	init_rage_button(data, &class->level[0].buttons[0]); 
	class->level[1].add_stats[STR] = 1;
	class->level[1].add_stats[CON] = 1;
	class->level[1].add_spell_slot[0] = 1;
	class->level[1].add_pv = 10;
	class->level[1].current_bonus_dice[D1] = 3;
	init_reckless_button(data, &class->level[1].buttons[0]);
	init_barbarian_class_2(data, class);
}
