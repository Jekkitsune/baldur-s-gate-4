/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:37:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/06 14:20:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	follow_party_member(t_data *data, t_entity *follower, t_entity *to_follow)
{
	if (follower == data->player.possession || follower->behavior.path || !follower->active || !follower->sheet.alive)
		return ;
	if (get_dist(follower->pos, to_follow->pos) > 2)
	{
		follower->behavior.path = get_path(data, follower->pos, to_follow->pos, true);
		if (!follower->behavior.path)
		{
			printf("%s: \"can't follow\"\n", follower->sheet.name);
			return ;
		}
		follower->behavior.next = follower->behavior.func;
		follower->behavior.func = entity_moving_to;
	}
}

void	party_follow(t_data *data)
{
	t_list	*party;

	party = data->round_manager.party;
	while (party)
	{
		if (!party->next)
			follow_party_member(data, party->content, data->round_manager.party->content);
		else
			follow_party_member(data, party->content, party->next->content);
		party = party->next;
	}
}

void	free_round_manager(t_data *data)
{
	t_list	*lst;
	t_list	*to_free;

	lst = data->round_manager.party;
	while (lst)
	{
		to_free = lst;
		lst = lst->next;
		free(to_free);
	}
	lst = data->round_manager.participants;
	while (lst)
	{
		to_free = lst;
		lst = lst->next;
		free(to_free);
	}
}
