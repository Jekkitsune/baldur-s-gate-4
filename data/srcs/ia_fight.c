/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_fight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:59:31 by fparis            #+#    #+#             */
/*   Updated: 2025/01/10 21:13:42 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_path_size(t_data *data, t_vector start, t_vector end)
{
	t_path	*path;
	t_path	*i;
	int		res;

	path = get_path(data, start, end, true);
	if (!path)
		return (-1);
	res = 0;
	i = path;
	while (i)
	{
		i = i->next;
		res++;
	}
	free_path(&path);
	return (res);
}

t_entity	*get_closest_target(t_data *data, t_entity *entity)
{
	t_entity	*closest;
	int			min_dist;
	t_entity	*current;
	int			cur_dist;
	t_list		*lst;

	closest = NULL;
	min_dist = -1;
	lst = data->round_manager.participants;
	while (lst)
	{
		current = lst->content;
		if (current != entity && current->sheet.team != entity->sheet.team)
		{
			cur_dist = get_path_size(data, entity->pos, current->pos);
			if (cur_dist != -1 && (min_dist == -1 || cur_dist < min_dist))
			{
				min_dist = cur_dist;
				closest = current;
			}
		}
		lst = lst->next;
	}
	return (closest);
}

void	compare_buttons(t_button **current_best, t_button *compare)
{
	int	current_average;
	int	compare_average;

	if (!*current_best)
	{
		*current_best = compare;
		return ;
	}
	current_average = get_dice_average((*current_best)->spellinfo.dice);
	compare_average = get_dice_average(compare->spellinfo.dice);
	if (compare_average > current_average)
		*current_best = compare;
}

t_button	*get_best_action(t_entity *entity, int min_range, t_spelltype type)
{
	t_button	*best;
	t_button	*current;
	int			i;

	i = 0;
	best = NULL;
	while (i < NB_BUTTON)
	{
		current = &entity->sheet.buttons[i];
		if (current)
		{
			current->spellinfo.caster = entity;
			if (current->spellinfo.type == type
				&& current->spellinfo.range >= min_range && check_action_cost(&current->spellinfo))
				compare_buttons(&best, current);
		}
		i++;
	}
	return (best);
}

t_bool	try_ia_action(t_data *data, t_entity *entity, t_entity *target, t_spellinfo spell)
{
	if (get_dist(entity->pos, target->pos) > spell.range
		|| has_obstacle(data, entity, target))
		return (false);
	spell.pos = target->pos;
	spell.pos_offset = target->offset;
	spell.target = target;
	spell.nb = roll(spell.dice);
	spell.caster = entity;
	if ((!spell.target_self && spell.target == spell.caster) || !check_action_cost(&spell))
		return (false);
	spell.caster->angle = atan2(spell.pos.y - spell.caster->pos.y, spell.pos.x - spell.caster->pos.x);
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

void	martial_try_attacks(t_data *data, t_entity *entity, t_button *best_button)
{
	if (best_button && try_ia_action(data, entity, entity->behavior.target, best_button->spellinfo))
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
	best_button = get_best_action(entity, get_dist(entity->pos, entity->behavior.target->pos), offensive);
	if (best_button && try_ia_action(data, entity, entity->behavior.target, best_button->spellinfo))
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
	best_button = get_best_action(entity, 1, offensive);
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
		if (get_dist(entity->pos, ((t_entity *)lst->content)->pos) < 4)
		{
			enter_combat(data, entity);
			return ;
		}
		lst = lst->next;
	}
}
