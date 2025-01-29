/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rogue_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:23:34 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 15:11:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rogue_end(t_data *data, t_class *class)
{
	class->level[2].add_stats[CON] = 2;
	class->level[2].add_pb = 1;
	class->level[2].add_pv = 9;
	class->level[2].current_bonus_dice[D6] = 2;
	class->level[2].properties = menaced_advantage | crit_1;
	class->level[3].add_stats[DEX] = 2;
	class->level[3].add_stats[INT] = 2;
	class->level[3].add_pv = 7;
	class->level[3].current_bonus_dice[D6] = 3;
	class->level[3].properties = true_sight;
	class->level[4].add_pb = 1;
	class->level[4].add_pv = 7;
	class->level[4].current_bonus_dice[D6] = 4;
	class->level[4].properties = crit_3;
	add_class(&data->class_lst, class);
}

void	init_rogue_class(t_data *data)
{
	t_class	*class;

	class = ft_calloc(sizeof(t_class), 1);
	if (!class)
		return ;
	class->name = "rogue";
	class->cast_stat = INT;
	class->level[0].add_pb = 2;
	class->level[0].current_bonus_dice[D6] = 1;
	init_steal_button(data, &class->level[0].buttons[0]);
	init_sneak_atk_button(data, &class->level[0].buttons[1]);
	class->level[1].add_stats[DEX] = 1;
	class->level[1].add_pv = 11;
	init_dash_bonus_button(data, &class->level[1].buttons[0]);
	class->level[1].current_bonus_dice[D6] = 2;
	init_rogue_end(data, class);
}
