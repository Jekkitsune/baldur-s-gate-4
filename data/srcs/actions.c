/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:45:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/17 00:46:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	*create_selector(t_data *data);

void	select_target(t_data *data)
{
	if (!data->player.arrow && in_bound(data->current_map, data->player.pos))
		data->player.arrow = create_selector(data);
	if (data->player.possession
		&& ft_strcmp(data->player.possession->current_anim->name, "select"))
		change_anim(data->player.possession, "select", true);
}

t_bool	check_dist_obstacle(t_data *data, t_entity *entity,
	float dist, t_bool visible_target)
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

void	execute_action(t_data *data, t_spellinfo *spell)
{
	remove_selector(data, true);
	spell->caster->angle = atan2(spell->pos.y - spell->caster->pos.y,
			spell->pos.x - spell->caster->pos.x);
	if (spell->anim)
		change_anim_next(spell->caster, spell->anim, "idle", true);
	if (spell->timer > 0)
		add_timer_effect(data, *spell, spell->timer, false);
	else
		spell->effect(data, spell);
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
		|| !check_dist_obstacle(data, entity, spell.range,
			spell.visible_target))
		return ;
	spell.pos = data->player.arrow->pos;
	spell.pos_offset = data->player.offset;
	spell.target = cycle_entity_cell(data, 0);
	if (!spell.nb)
		spell.nb = roll(spell.dice);
	spell.caster = entity;
	if ((!spell.target_self && spell.target == spell.caster)
		|| !check_action_cost(&spell))
		return ;
	execute_action(data, &spell);
}
