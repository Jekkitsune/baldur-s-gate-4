/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_throw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 07:40:15 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 17:02:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	execute_action(t_data *data, t_spellinfo *spell);
void	apply_cell(t_data *data, t_cell cell, t_spellinfo spell,
		void (*effect)(void *data, t_entity *target, t_entity *caster, int nb));

t_vector	throw_pos(t_data *data, t_vector pos)
{
	if (is_empty_cell(data, pos))
		return (pos);
	if (is_empty_cell(data, vec(pos.x - 1, pos.y)))
		return (vec(pos.x - 1, pos.y));
	if (is_empty_cell(data, vec(pos.x + 1, pos.y)))
		return (vec(pos.x + 1, pos.y));
	if (is_empty_cell(data, vec(pos.x, pos.y - 1)))
		return (vec(pos.x, pos.y - 1));
	if (is_empty_cell(data, vec(pos.x, pos.y + 1)))
		return (vec(pos.x, pos.y + 1));
	return (pos);
}

void	man_throw(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !apply_action_cost(data, spell))
		return ;
	damage_cell(data, spell->pos, spell->nb);
	damage(data, spell->target, spell->nb);
	teleport_entity(data, spell->target, throw_pos(data, spell->pos),
		vecf(0, 0));
}

void	man_throw_launch_pos(t_data *data, t_spellinfo spell, t_entity *entity)
{
	if (vec_cmp(data->player.arrow->pos, spell.target->pos)
		|| !check_dist_obstacle(data, entity, spell.range, spell.visible_target))
		return ;
	spell.pos = data->player.arrow->pos;
	spell.pos_offset = data->player.offset;
	spell.nb = roll(spell.dice);
	spell.caster = entity;
	if ((!spell.target_self && spell.target == spell.caster)
		|| !check_action_cost(&spell))
		return ;
	execute_action(data, &spell);
}

void	man_throw_select(void *data_param, void *entity_param,
		t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = entity_param;
	if (!data->player.arrow)
		select_target(data);
	if (!spell.target)
	{
		data->player.active_button->spellinfo.range = 1.5;
		if (!spell.effect || !check_dist_obstacle(data, entity, spell.range,
				spell.visible_target) || !confirm(data->player.active_button))
			return ;
		data->player.active_button->spellinfo.target =
			cycle_entity_cell(data, 0);
		data->player.active_button->spellinfo.range = 5;
		return ;
	}
	man_throw_launch_pos(data, spell, entity);
}

void	init_man_throw_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 5;
	button->spellinfo.dice[D6] = 1;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = man_throw;
	button->spellinfo.type = check_type;
	button->spellinfo.cost_bonus = 1;
	button->func = man_throw_select;
	button->img = get_tex(data, "man_throw_button");
	button->spellinfo.anim = "range";
	button->spellinfo.timer = 0.5;
	button->name = "Man throw";
	button->description = "Select an ennemy or object, then where to throw \
them, 1d6 to launched and potential target";
}
