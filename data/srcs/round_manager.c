/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:04:23 by fparis            #+#    #+#             */
/*   Updated: 2025/01/09 12:33:59 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_turn(t_data *data)
{
	t_list	*lst;
	t_list	*first;

	first = data->round_manager.participants;
	lst = first;
	while (lst->next)
		lst = lst->next;
	if (lst == first)
		leave_combat(data, lst->content);
	else
	{
		data->round_manager.participants = first->next;
		first->next = NULL;
		lst->next = first;
		round_refresh_stat(lst->content);
	}
}

t_bool	is_current_turn(t_data *data, t_entity *entity)
{
	if (!data->round_manager.combat || !data->round_manager.participants
		|| entity == data->round_manager.participants->content)
		return (true);
	return (false);
}

t_bool	in_combat(t_data *data)
{
	t_list		*list;
	t_entity	*current;
	int			team;

	list = data->round_manager.participants;
	if (!list)
		return (false);
	current = list->content;
	team = current->sheet.team;
	list = list->next;
	while (list)
	{
		current = list->content;
		if (current->sheet.team != team)
			return (true);
		list = list->next;
	}
	return (false);
}

void	check_combat_end(t_data *data)
{
	t_bool		combat;
	t_list		*lst;

	combat = in_combat(data);
	lst = data->round_manager.participants;
	if (lst && !combat)
	{
		while (lst)
		{
			leave_combat(data, lst->content);
			lst = lst->next;
		}
	}	
}

void	party_refresh(t_data *data)
{
	t_list					*lst;
	static unsigned long	last_sec = 0;

	if (last_sec < data->current_time.tv_sec)
	{
		last_sec = data->current_time.tv_sec + 6;
		lst = data->round_manager.party;
		while (lst)
		{
			round_refresh_stat(lst->content);
			lst = lst->next;
		}
	}
}
