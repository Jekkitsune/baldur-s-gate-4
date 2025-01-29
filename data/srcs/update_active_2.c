/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_active_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:37:46 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 14:38:26 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ai_play(t_data *data, t_entity *current)
{
	if (!is_turn(data, current))
		return ;
	if (data->round_manager.combat)
	{
		if (current->possess_control)
			return ;
		if (!current->behavior.func || !current->sheet.alive)
			next_turn(data);
		else
			current->behavior.func(data, current);
	}
	else if (current->behavior.func && data->player.possession != current)
		current->behavior.func(data, current);
}

void	apply_spelltype_filter_color(t_data *data, t_entity *entity)
{
	if (!data->player.active_button)
		return ;
	if (data->player.active_button->spellinfo.type == offensive
		|| data->player.active_button->spellinfo.type == debuff)
		entity_filter(entity, 0xFFAA0000);
	else if (data->player.active_button->spellinfo.type == heal
		|| data->player.active_button->spellinfo.type == buff)
		entity_filter(entity, 0xFF00AA00);
	else
		entity_filter(entity, 0xFF888888);
}

void	show_advantage(t_data *data, t_spellinfo *info)
{
	int			has_advantage;
	t_strput	*to_put;
	t_vector	pos;

	has_advantage = advantage(data, info->caster, info->target);
	if (has_advantage == 0)
		return ;
	to_put = NULL;
	pos = vec(data->win_size.x / 2, data->win_size.y / 2);
	if (has_advantage == 1)
		to_put = strput(ft_strdup("ADVANTAGE"), pos, 30, 0xFF00AA00);
	else if (has_advantage == -1)
		to_put = strput(ft_strdup("DISADVANTAGE"), pos, 30, 0xFFAA0000);
	screen_string_put(data, to_put, 0);
}
