/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:10:49 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 00:18:20 by fparis           ###   ########.fr       */
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

void	insert_in_combat(t_data *data, t_list *new, int initiative)
{
	t_list	*i_lst;
	t_list	*last_lst;

	i_lst = data->round_manager.participants;
	if (!i_lst)
	{
		data->round_manager.participants = new;
		return ;
	}
	last_lst = NULL;
	while (i_lst && ((t_entity *)i_lst->content)->sheet.initiative >= initiative)
	{
		last_lst = i_lst;
		i_lst = i_lst->next;
	}
	if (last_lst)
		last_lst->next = new;
	else
		data->round_manager.participants = new;
	new->next = i_lst;
}

void	roll_initiative(t_data *data, t_entity *entity)
{
	int		initiative;

	round_refresh_stat(entity);
	entity->sheet.in_fight = true;
	initiative = roll_one(20, 1) + modif(entity->sheet.stats[DEX]);
	show_info(data, "%s rolled %d to initiative.", entity->sheet.name, initiative);
	entity->sheet.initiative = initiative;
}

void	get_party_combat(t_data *data)
{
	t_list		*lst;
	t_list		*new;
	t_entity	*current;

	lst = data->round_manager.party;
	while (lst && lst->content)
	{
		current = lst->content;
		change_anim(current, "idle", true);
		roll_initiative(data, current);
		new = ft_lstnew(current);
		if (!new)
			return ;
		insert_in_combat(data, new, current->sheet.initiative);
		lst = lst->next;
	}
}

void join_ally_fight(void *data, t_entity *target, t_entity *caster, __attribute__((unused)) int nb)
{
	if (target && !target->sheet.in_fight && caster && target->sheet.team == caster->sheet.team)
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

void	enter_combat(t_data *data, t_entity *entity)
{
	t_list	*new;

	if (!entity || !data->round_manager.party || !entity->sheet.alive || entity->sheet.in_fight)
		return ;
	if (!data->round_manager.combat)
	{
		data->round_manager.combat = true;
		show_info(data, "Enter Combat:\n");
		get_party_combat(data);
	}
	change_anim(entity, "idle", true);
	roll_initiative(data, entity);
	new = ft_lstnew(entity);
	if (!new)
		return ;
	insert_in_combat(data, new, entity->sheet.initiative);
	free_path(&entity->behavior.path);
	entity->behavior.func = entity->sheet.fight_ia;
	call_allies(data, entity);
}
