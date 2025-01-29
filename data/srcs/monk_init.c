/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monk_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:18:16 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 19:16:47 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_monk_end(t_data *data, t_class *class)
{
	class->level[2].add_spell_slot[0] = 2;
	class->level[2].add_stats[WIS] = 2;
	class->level[2].add_pb = 1;
	class->level[2].add_pv = 6;
	class->level[2].current_bonus_dice[D6] = 1;
	class->level[2].add_speed = 2;
	class->level[2].add_nb_attack = 1;
	init_step_wind_button(data, &class->level[2].buttons[0]);
	class->level[3].current_bonus_dice[D6] = 1;
	class->level[3].add_spell_slot[0] = 2;
	class->level[3].add_stats[DEX] = 2;
	class->level[3].add_stats[CON] = 2;
	class->level[3].add_pv = 10;
	init_stunning_strike_button(data, &class->level[3].buttons[0]);
	class->level[4].current_bonus_dice[D8] = 1;
	class->level[4].add_pb = 1;
	class->level[4].add_pv = 7;
	class->level[4].add_speed = 2;
	class->level[4].add_spell_slot[0] = 2;
	class->level[4].properties = healing_hand_plus;
	add_class(&data->class_lst, class);
}

void	init_monk_class(t_data *data)
{
	t_class	*class;

	class = ft_calloc(sizeof(t_class), 1);
	if (!class)
		return ;
	class->name = "monk";
	class->cast_stat = WIS;
	class->level[0].add_spell_slot[0] = 4;
	class->level[0].add_pb = 2;
	class->level[0].add_speed = 2;
	class->level[0].current_bonus_dice[D4] = 1;
	class->level[0].properties = spiritual_defense | bare_hands_master;
	init_bonus_punch_button(data, &class->level[0].buttons[0]);
	class->level[1].add_spell_slot[0] = 2;
	class->level[1].add_stats[DEX] = 1;
	class->level[1].add_pv = 6;
	class->level[1].current_bonus_dice[D4] = 1;
	init_flurry_button(data, &class->level[1].buttons[0]);
	init_healing_hands_button(data, &class->level[1].buttons[1]);
	init_monk_end(data, class);
}
