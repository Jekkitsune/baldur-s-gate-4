/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ranger.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:23:29 by fparis            #+#    #+#             */
/*   Updated: 2025/01/29 12:25:06 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ranger_end(t_data *data, t_class *class)
{
	class->level[2].current_bonus_dice[D8] = 1;
	class->level[2].add_spell_slot[1] = 1;
	class->level[2].add_stats[WIS] = 2;
	class->level[2].add_pb = 1;
	class->level[2].add_pv = 7;
	class->level[2].add_nb_attack = 1;
	init_special_arrow_button(data, &class->level[2].buttons[0], silenced);
	class->level[3].current_bonus_dice[D8] = 1;
	class->level[3].add_stats[DEX] = 2;
	class->level[3].add_stats[CON] = 2;
	class->level[3].add_pv = 9;
	class->level[3].add_spell_slot[1] = 1;
	init_sharp_shooter_button(data, &class->level[3].buttons[0]);
	init_arrow_rain_button(data, &class->level[3].buttons[1]);
	class->level[4].current_bonus_dice[D10] = 1;
	class->level[4].add_pb = 1;
	class->level[4].add_pv = 8;
	class->level[4].add_spell_slot[0] = 1;
	class->level[4].add_spell_slot[1] = 1;
	class->level[4].properties = master_hunter;
	add_class(&data->class_lst, class);
}

void	init_ranger_class(t_data *data)
{
	t_class	*class;

	class = ft_calloc(sizeof(t_class), 1);
	if (!class)
		return ;
	class->name = "ranger";
	class->cast_stat = WIS;
	class->level[0].current_bonus_dice[D6] = 1;
	class->level[0].add_spell_slot[0] = 2;
	class->level[0].add_pb = 2;
	class->level[0].properties = master_archer;
	init_hunter_mark_button(data, &class->level[0].buttons[0]);
	init_special_arrow_button(data, &class->level[0].buttons[1], acid);
	class->level[1].current_bonus_dice[D6] = 1;
	class->level[1].add_stats[DEX] = 1;
	class->level[1].add_pv = 7;
	class->level[1].add_spell_slot[0] = 1;
	class->level[1].properties = close_shooter;
	init_special_arrow_button(data, &class->level[1].buttons[0], restrained);
	init_ranger_end(data, class);
}
