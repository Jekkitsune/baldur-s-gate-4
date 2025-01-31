/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_fights_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 00:06:02 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 01:42:54 by fparis           ###   ########.fr       */
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

t_bool	targetable(t_entity *caster, t_entity *target)
{
	float	distance;

	if (!caster || !target)
		return (false);
	distance = get_dist(caster->pos, target->pos);
	if (target->sheet.properties & banished)
		return (false);
	if (target->sheet.properties & invisible && distance >= 2
		&& !(caster->sheet.properties & true_sight))
		return (false);
	return (true);
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
		if (current && current != entity && current->sheet.team
			!= entity->sheet.team && targetable(entity, current))
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

void	compare_buttons(t_data *data, t_button **current_best,
	t_button *compare, t_entity *entity)
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
	if (compare_average >= current_average
		&& get_best_spell_pos(data, &compare->spellinfo, entity))
		*current_best = compare;
}

t_button	*get_best_action(t_data *data, t_entity *entity, int min_range,
	t_spelltype type)
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
				&& current->func == action_select
				&& current->spellinfo.range >= min_range
				&& check_action_cost(&current->spellinfo))
				compare_buttons(data, &best, current, entity);
		}
		i++;
	}
	return (best);
}
