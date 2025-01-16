/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_fight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:59:31 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 00:07:59 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	try_ia_action(t_data *data, t_entity *entity, t_entity *target,
	t_spellinfo spell)
{
	if (get_dist(entity->pos, target->pos) > spell.range
		|| has_obstacle(data, entity, target))
		return (false);
	spell.caster = entity;
	spell.target = target;
	if (spell.radius < 2)
	{
		spell.pos = target->pos;
		spell.pos_offset = target->offset;
	}
	spell.nb = roll(spell.dice);
	if ((!spell.target_self && spell.target == spell.caster)
		|| !check_action_cost(&spell))
		return (false);
	spell.caster->angle = atan2(spell.pos.y - spell.caster->pos.y, spell.pos.x
			- spell.caster->pos.x);
	if (spell.anim)
		change_anim_next(spell.caster, spell.anim, "idle", true);
	if (spell.timer > 0)
		add_timer_effect(data, spell, spell.timer, false);
	else
		spell.effect(data, &spell);
	return (true);
}

void	reset_behavior(t_data *data, t_entity *entity, t_bool end_turn)
{
	free_path(&entity->behavior.path);
	entity->behavior.target = NULL;
	entity->behavior.func = entity->sheet.fight_ia;
	if (end_turn)
		next_turn(data);
}

void	martial_try_attacks(t_data *data, t_entity *entity,
	t_button *best_button)
{
	if (best_button && try_ia_action(data, entity, entity->behavior.target,
			best_button->spellinfo))
	{
		reset_behavior(data, entity, false);
		return ;
	}
	else if (entity->sheet.walked > 0)
	{
		if (!entity->behavior.path)
			move_closest_to(data, entity, entity->behavior.target);
		if (!entity->behavior.path)
			reset_behavior(data, entity, true);
		return ;
	}
	best_button = get_best_action(data, entity,
			get_dist(entity->pos, entity->behavior.target->pos), offensive);
	if (best_button && try_ia_action(data, entity, entity->behavior.target,
			best_button->spellinfo))
	{
		reset_behavior(data, entity, false);
		return ;
	}
	reset_behavior(data, entity, true);
}

void	martial_ia(void *data_param, void *entity_param)
{
	t_entity	*entity;
	t_data		*data;
	t_button	*best_button;

	data = data_param;
	entity = entity_param;
	if (entity->anim_no_move)
		return ;
	if (!entity->behavior.target)
		entity->behavior.target = get_closest_target(data, entity);
	best_button = get_best_action(data, entity, 1, offensive);
	if (!entity->behavior.target || !best_button)
	{
		reset_behavior(data, entity, true);
		return ;
	}
	martial_try_attacks(data, entity, best_button);
}

void	base_aggro(void *data_param, void *entity_param)
{
	t_entity	*entity;
	t_data		*data;
	t_list		*lst;

	data = data_param;
	entity = entity_param;
	lst = data->round_manager.party;
	if (!entity || entity->behavior.path)
		return ;
	while (lst)
	{
		if (lst->content && ((t_entity *)lst->content)->sheet.alive
			&& get_dist(entity->pos, ((t_entity *)lst->content)->pos) < 4)
		{
			enter_combat(data, entity);
			return ;
		}
		lst = lst->next;
	}
}
