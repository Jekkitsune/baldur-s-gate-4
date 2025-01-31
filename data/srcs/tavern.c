/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tavern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:46:28 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 13:35:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	party_long_rest(t_data *data)
{
	t_list		*lst;
	t_entity	*current;

	lst = data->round_manager.party;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current)
		{
			long_rest(data, current);
			if (data->player.possession)
				teleport_entity(data, current, data->player.possession->pos,
					vecf(0, 0));
		}
	}
}

void	tavern_effect(t_data *data)
{
	if (data->player.gold >= 30)
	{
		show_info(data, "You paid the tavern 30 gold");
		data->player.gold -= 30;
		party_long_rest(data);
	}
	else
		show_info(data, "Not enough money to pay the tavern...");
}
