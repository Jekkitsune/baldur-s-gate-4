/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_property_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 04:23:13 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 17:04:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	break_concentration(t_data *data, t_entity *entity,
		int id_concentration)
{
	t_list				*lst;
	t_timer_property	*current;

	lst = entity->sheet.timer_concentration;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current && (!id_concentration || current->id_concentration
				== id_concentration))
			pop_free_property(data, current);
	}
	entity->sheet.concentration = 0;
}

void	remove_cell_property(t_data *data, t_timer_property *prop)
{
	t_list	**lst;
	t_list	*entity_lst;
	t_list	*tmp;

	lst = &prop->cell->timer_property;
	tmp = ft_lstpop(lst, prop);
	free(tmp);
	entity_lst = prop->cell->entities;
	while (entity_lst)
	{
		((t_entity *)entity_lst->content)->sheet.properties &= ~prop->property;
		refresh_stats(data, entity_lst->content);
		entity_lst = entity_lst->next;
	}
}

void	pop_free_property(t_data *data, t_timer_property *prop)
{
	t_list	**lst;
	t_list	*tmp;

	if (prop->entity)
	{
		prop->entity->sheet.properties &= ~prop->property;
		lst = &prop->entity->sheet.timer_property;
		tmp = ft_lstpop(lst, prop);
		free(tmp);
		refresh_stats(data, prop->entity);
	}
	if (prop->cell)
		remove_cell_property(data, prop);
	if (prop->caster)
	{
		lst = &prop->caster->sheet.timer_concentration;
		tmp = ft_lstpop(lst, prop);
		free(tmp);
	}
	free(prop);
}

void	add_cell_property_entity(t_data *data, t_entity *entity)
{
	t_list				*lst;
	t_timer_property	*current;

	if (!in_bound(data->current_map, entity->pos))
		return ;
	lst = data->current_map->arr[entity->pos.x][entity->pos.y].timer_property;
	if (!lst)
		return ;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current)
			entity->sheet.properties |= current->property;
	}
	refresh_stats(data, entity);
}

void	remove_cell_property_entity(t_data *data, t_entity *entity,
	t_vector last_pos)
{
	t_list				*lst;
	t_timer_property	*current;

	if (!in_bound(data->current_map, last_pos))
		return ;
	lst = data->current_map->arr[last_pos.x][last_pos.y].timer_property;
	if (!lst)
		return ;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current)
			entity->sheet.properties &= ~current->property;
	}
	refresh_stats(data, entity);
}
