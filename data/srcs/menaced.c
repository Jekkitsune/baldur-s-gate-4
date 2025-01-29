/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menaced.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:57:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 13:15:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	menace_cell(t_cell *cell, int team, t_entity *banned)
{
	t_list		*lst;
	t_entity	*current;

	if (!cell)
		return (false);
	lst = cell->entities;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current && (current->sheet.type != living || !current->sheet.alive))
			continue ;
		if (current != banned && current->sheet.team != team)
			return (true);
	}
	return (false);
}

t_bool	is_menaced(t_data *data, t_entity *entity, t_entity *banned)
{
	t_vector	pos;

	if (!entity)
		return (false);
	pos = entity->pos;
	pos.x = entity->pos.x - 1;
	while (pos.x <= entity->pos.x + 1)
	{
		pos.y = entity->pos.y - 1;
		while (pos.y <= entity->pos.y + 1)
		{
			if (in_bound(data->current_map, pos)
				&& menace_cell(&data->current_map->arr[pos.x][pos.y],
				entity->sheet.team, banned))
				return (true);
			pos.y++;
		}
		pos.x++;
	}
	return (false);
}
