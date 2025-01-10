/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:45:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/10 19:14:10 by fparis           ###   ########.fr       */
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
	res = spawn_entity(data, get_prefab(data, "selector"), data->player.pos, ft_strjoin("selector", ""));
	change_anim(res, "idle", true);
	if (!res)
		return (NULL);
	possess_control(res, true);
	if (data->player.possession)
		teleport_entity(data, res, data->player.possession->pos, data->player.possession->offset);
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
	if (data->player.possession && !ft_strcmp(data->player.possession->current_anim->name, "select"))
		change_anim(data->player.possession, "idle", true);
}

void	select_target(t_data *data)
{
	if (!data->player.arrow && in_bound(data->current_map, data->player.pos))
		data->player.arrow = create_selector(data);
	if (data->player.possession && ft_strcmp(data->player.possession->current_anim->name, "select"))
		change_anim(data->player.possession, "select", true);
}

t_bool	check_dist_obstacle(t_data *data, t_entity *entity, float dist, t_bool visible_target)
{
	if (!entity || !data->player.arrow)
		return (false);
	if (get_dist(entity->pos, data->player.arrow->pos) > dist || (visible_target
		&& has_obstacle(data, data->player.possession, data->player.arrow)))
	{
		if (data->player.arrow->current_anim
			&& ft_strcmp(data->player.arrow->current_anim->name, "death"))
				change_anim(data->player.arrow, "dead", true);
		return (false);
	}
	else if (data->player.arrow->current_anim
		&& ft_strcmp(data->player.arrow->current_anim->name, "idle"))
			change_anim(data->player.arrow, "idle", true);
	return (true);
}

void	action_select(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = entity_param;
	if (!data->player.arrow)
		select_target(data);
	if (!confirm(data->player.active_button) || !spell.effect
		|| !check_dist_obstacle(data, entity, spell.range, spell.visible_target))
		return ;
	spell.pos = data->player.arrow->pos;
	spell.pos_offset = data->player.offset;
	spell.target = cycle_entity_cell(data, 0);
	spell.nb = roll(spell.dice);
	spell.caster = entity;
	if ((!spell.target_self && spell.target == spell.caster) || !check_action_cost(&spell))
		return ;
	remove_selector(data, true);
	spell.caster->angle = atan2(spell.pos.y - spell.caster->pos.y, spell.pos.x - spell.caster->pos.x);
	if (spell.anim)
		change_anim_next(spell.caster, spell.anim, "idle", true);
	if (spell.timer > 0)
		add_timer_effect(data, spell, spell.timer, false);
	else
		spell.effect(data, &spell);
}
