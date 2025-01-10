/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:04:23 by fparis            #+#    #+#             */
/*   Updated: 2025/01/10 20:36:46 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_turn(t_data *data)
{
	t_list	*lst;
	t_list	*first;

	if (!data->round_manager.combat)
		return ;
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

t_bool	is_turn(t_data *data, t_entity *entity)
{
	if (!data->round_manager.combat || !data->round_manager.participants
		|| entity == data->round_manager.participants->content)
		return (true);
	return (false);
}

void	party_refresh(t_data *data)
{
	t_list			*lst;
	static time_t	last_sec = 0;

	if (!data->round_manager.combat && last_sec < data->current_time.tv_sec)
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
