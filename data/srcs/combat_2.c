/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:08:50 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 19:00:49 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_combat(t_data *data)
{
	t_list		*lst;
	t_list		*to_free;
	t_entity	*entity;

	lst = data->round_manager.participants;
	while (lst)
	{
		entity = lst->content;
		if (entity)
		{
			entity->sheet.in_fight = false;
			if (entity->sheet.alive)
				entity->behavior.func = entity->sheet.wander_ia;
		}
		lst = lst->next;
		to_free = ft_lstpop(&data->round_manager.participants, entity);
		if (to_free)
			free(to_free);
	}
	if (!data->round_manager.participants)
		data->round_manager.combat = false;
	if (data->round_manager.party)
		smooth_possess(data, data->round_manager.party->content);
}

void	check_combat_end(t_data *data)
{
	t_list		*list;
	t_entity	*current;
	int			team;

	list = data->round_manager.participants;
	if (!list)
		return ;
	current = list->content;
	team = current->sheet.team;
	list = list->next;
	if (!list)
	{
		end_combat(data);
		return ;
	}
	while (list)
	{
		current = list->content;
		if (current->sheet.team != team)
			return ;
		list = list->next;
	}
	end_combat(data);
}

void	leave_combat(t_data *data, t_entity *entity)
{
	t_list	*lst;

	if (!entity)
		return ;
	entity->sheet.in_fight = false;
	if (entity->sheet.alive)
		entity->behavior.func = entity->sheet.wander_ia;
	lst = ft_lstpop(&data->round_manager.participants, entity);
	if (lst)
		free(lst);
	if (!data->round_manager.participants)
		data->round_manager.combat = false;
	check_combat_end(data);
}

void	join_ally_fight(void *data, t_entity *target, t_entity *caster,
	__attribute__((unused)) int nb)
{
	if (target && !target->sheet.in_fight && caster && target->sheet.team
		== caster->sheet.team)
		enter_combat(data, target);
}

void	call_allies(t_data *data, t_entity *entity)
{
	t_spellinfo	info;

	info.radius = 4;
	info.pos = entity->pos;
	info.caster = entity;
	info.nb = entity->sheet.team;
	zone_effect(data, info, join_ally_fight);
}
