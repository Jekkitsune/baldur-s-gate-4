/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:10:49 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 14:10:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	call_allies(t_data *data, t_entity *entity);

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
	while (i_lst && ((t_entity *)i_lst->content)->sheet.initiative
		>= initiative)
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
	show_info(data, "%s rolled %d to initiative.",
		entity->sheet.name, initiative);
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
		if (current->sheet.alive)
		{
			change_anim(current, "idle", true);
			roll_initiative(data, current);
			new = ft_lstnew(current);
			if (!new)
				return ;
			insert_in_combat(data, new, current->sheet.initiative);
		}
		lst = lst->next;
	}
}

void	enter_combat(t_data *data, t_entity *entity)
{
	t_list	*new;

	if (!entity || !data->round_manager.party || !entity->sheet.alive
		|| entity->sheet.in_fight)
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
