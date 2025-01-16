/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:43:48 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 17:44:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	check_action_cost(t_spellinfo *spell)
{
	t_sheet		*sheet;

	if (!spell->caster)
		return (false);
	sheet = &spell->caster->sheet;
	if (spell->cost_attack)
	{
		if (sheet->attack_left <= 0 && sheet->action <= 0)
			return (false);
	}
	else if (spell->cost_action && sheet->action <= 0)
		return (false);
	if (spell->cost_bonus && sheet->bonus_action <= 0)
		return (false);
	if (spell->cost_spell_slot > 0 && spell->cost_spell_slot < SPELL_MAX_LV
		&& sheet->spell_slot[spell->cost_spell_slot - 1] <= 0)
		return (false);
	return (true);
}

t_bool	apply_action_cost(t_spellinfo *spell)
{
	t_sheet		*sheet;

	if (!spell->caster)
		return (false);
	sheet = &spell->caster->sheet;
	if (spell->cost_attack)
	{
		if (sheet->attack_left <= 0 && sheet->action)
		{
			sheet->action--;
			sheet->attack_left = sheet->nb_attack - 1;
		}
		else if (sheet->attack_left-- <= 0)
			return (false);
	}
	else if (spell->cost_action && sheet->action-- <= 0)
		return (false);
	if (spell->cost_bonus && sheet->bonus_action-- <= 0)
		return (false);
	if (spell->cost_spell_slot > 0 && spell->cost_spell_slot < SPELL_MAX_LV
		&& sheet->spell_slot[spell->cost_spell_slot - 1]-- <= 0)
		return (false);
	return (true);
}

t_bool	confirm(t_button *pushed)
{
	static t_button	*check = NULL;

	if (pushed && pushed == check)
	{
		check = NULL;
		return (true);
	}
	check = pushed;
	return (false);
}

t_entity	*create_selector(t_data *data)
{
	t_entity	*res;

	data->player.last_angle.x = data->player.angle;
	data->player.last_angle.y = data->player.focus_dist;
	res = spawn_entity(data, get_prefab(data, "selector"),
			data->player.pos, ft_strjoin("selector", ""));
	change_anim(res, "idle", true);
	if (!res)
		return (NULL);
	possess_control(res, true);
	if (data->player.possession)
		teleport_entity(data, res, data->player.possession->pos,
			data->player.possession->offset);
	return (res);
}

void	remove_selector(t_data *data, t_bool reset_angle)
{
	if (reset_angle)
	{
		data->player.angle = data->player.last_angle.x;
		data->player.focus_dist = data->player.last_angle.y;
	}
	confirm(NULL);
	if (data->player.active_button)
	{
		data->player.active_button->active = false;
		data->player.active_button = NULL;
	}
	if (data->player.arrow)
		destroy_entity(data, data->player.arrow);
	if (data->player.possession
		&& !ft_strcmp(data->player.possession->current_anim->name, "select"))
		change_anim(data->player.possession, "idle", true);
}
