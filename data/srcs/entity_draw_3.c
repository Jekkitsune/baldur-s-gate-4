/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_draw_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:00:28 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 22:49:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	draw_invisible(t_data *data, t_entity *entity)
{
	t_list		*lst;
	t_entity	*current;

	if (data->player.possession && entity->sheet.properties & invisible
		&& !in_party(data, entity))
	{
		lst = data->round_manager.party;
		while (lst)
		{
			current = lst->content;
			if (current && (get_dist(current->pos, entity->pos) < 2
				|| current->sheet.properties & true_sight))
				return (true);
			return (false);
			lst = lst->next;
		}
	}
	return (true);
}

t_bool	dont_draw(t_data *data, t_entity *entity)
{
	if (entity->sheet.type == effect)
		return (false);
	if (!draw_invisible(data, entity))
		return (true);
	if (entity->sheet.properties & banished)
		return (true);
	return (false);
}
