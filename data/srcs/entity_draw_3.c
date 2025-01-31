/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_draw_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:00:28 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:41:59 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_entity(t_data *data, t_entity *entity);

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

void	draw_closest(t_data *data, t_list **entities_lst,
	t_fog **fog_lst, float diff)
{
	t_entity	*current_entity;

	current_entity = NULL;
	if (*entities_lst)
		current_entity = (*entities_lst)->content;
	if (*fog_lst && (!current_entity
			|| (*fog_lst)->length >= current_entity->distance))
	{
		draw_fog(data, diff, *fog_lst);
		*fog_lst = (*fog_lst)->next;
	}
	else if (current_entity)
	{
		if (current_entity->nb_impact)
			draw_entity(data, current_entity);
		current_entity->nb_impact = 0;
		*entities_lst = (*entities_lst)->next;
	}
}

void	draw_entities_fog(t_data *data, float diff)
{
	t_list		*entities_lst;
	t_fog		*fog_lst;

	entities_lst = data->player.visible_entities;
	fog_lst = data->player.visible_fog;
	while (entities_lst || fog_lst)
	{
		while (entities_lst && !entities_lst->content)
			entities_lst = entities_lst->next;
		draw_closest(data, &entities_lst, &fog_lst, diff);
	}
	free_visible_lst(data);
}
