/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 01:52:01 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 13:35:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	follow_party_member(t_data *data, t_entity *follower,
	t_entity *to_follow)
{
	if (follower == data->player.possession || follower->behavior.path
		|| !follower->active || !follower->sheet.alive)
		return ;
	if (get_dist(follower->pos, to_follow->pos) > 2)
		move_closest_to(data, follower, to_follow);
}

void	party_follow(t_data *data)
{
	t_list	*party;

	if (data->round_manager.combat)
		return ;
	party = data->round_manager.party;
	while (party)
	{
		if (!party->next)
			follow_party_member(data, party->content,
				data->round_manager.party->content);
		else
			follow_party_member(data, party->content, party->next->content);
		party = party->next;
	}
}

void	leave_party(t_data *data, t_entity *entity)
{
	t_list	*lst;

	lst = NULL;
	lst = ft_lstpop(&data->round_manager.party, entity);
	free(lst);
}

t_bool	in_party(t_data *data, t_entity *entity)
{
	t_list	*lst;

	lst = data->round_manager.party;
	while (lst)
	{
		if (lst->content == entity)
			return (true);
		lst = lst->next;
	}
	return (false);
}
