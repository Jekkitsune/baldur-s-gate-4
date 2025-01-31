/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   travel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:14:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 04:19:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_cell_property_entity(t_data *data, t_entity *entity,
			t_vector last_pos);

t_vector	get_start_pos(t_map *new_map, t_map *last_map)
{
	t_vector	i;

	i.x = 0;
	while (i.x < new_map->size.x)
	{
		i.y = 0;
		while (i.y < new_map->size.y)
		{
			if (new_map->arr[i.x][i.y].travel == last_map)
				return (i);
			i.y++;
		}
		i.x++;
	}
	return (vec(-1, -1));
}

void	re_active_party(t_data *data)
{
	t_list		*lst;
	t_entity	*current;

	lst = data->round_manager.party;
	while (lst)
	{
		current = lst->content;
		add_active(data, current, current->sheet.wander_ia);
		lst = lst->next;
	}
}

void	change_party_map(t_data *data, t_map *new_map, t_vector pos)
{
	t_list		*lst;
	t_entity	*current;
	t_list		**new_cell_lst;
	t_list		*cell_lst;

	new_cell_lst = &new_map->arr[pos.x][pos.y].entities;
	lst = data->round_manager.party;
	while (lst)
	{
		current = lst->content;
		break_concentration(data, current, 0);
		destroy_active(data, current);
		remove_cell_property_entity(data, current, current->pos);
		cell_lst = ft_lstpop(&data->current_map->\
		arr[current->pos.x][current->pos.y].entities, current);
		cell_lst->next = NULL;
		ft_lstadd_back(new_cell_lst, cell_lst);
		current->pos = pos;
		current->offset = vecf(0, 0);
		lst = lst->next;
	}
	data->current_map = new_map;
	re_active_party(data);
}

t_bool	travel(t_data *data, t_map *new_map)
{
	t_vector	pos;

	if (!new_map || data->round_manager.combat)
		return (false);
	pos = get_start_pos(new_map, data->current_map);
	if (pos.x == -1)
		return (false);
	change_party_map(data, new_map, pos);
	return (true);
}
