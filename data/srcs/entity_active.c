/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_active.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:24:17 by fparis            #+#    #+#             */
/*   Updated: 2024/11/02 21:57:02 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_all_active(t_data *data)
{
	t_list		*i;
	t_entity	*current;

	i = data->current_map->active_entities;
	while (i)
	{
		current = i->content;
		i = i->next;
		current->behavior(data, current);
	}
}

t_bool	check_activity(t_data *data, t_entity *entity)
{
	t_list	*i;

	if (entity->active)
		return (true);
	i = data->current_map->active_entities;
	while (i)
	{
		if (i->content == entity)
		{
			entity->active = true;
			return (true);
		}
		i = i->next;
	}
	entity->active = false;
	return (false);
}

void	add_active(t_data *data, t_entity *entity, void (*behavior)(void *, void *))
{
	t_list	*new_lst;

	new_lst = ft_lstnew(entity);
	if (!new_lst)
	{
		destroy_entity(data, entity);
		return ;
	}
	new_lst->content = entity;
	entity->behavior = behavior;
	entity->active = 1;
	ft_lstadd_back(&data->current_map->active_entities, new_lst);
}

void	remove_active(t_data *data, t_entity *entity)
{
	t_list	*to_free;
	
	entity->active = 0;
	if (in_bound(*data->current_map, entity->pos))
	{
		if (ft_inlst(data->current_map->arr[entity->pos.x][entity->pos.y].entities, entity))
		{
			to_free = ft_lstpop(&data->current_map->active_entities, entity);
			if (to_free)
			{
				free(to_free);
				return ;
			}
		}
	}
	destroy_entity(data, entity);
}

void	destroy_active(t_data *data, t_entity *entity)
{
	t_list	*to_free;

	to_free = ft_lstpop(&data->current_map->active_entities, entity);
	if (to_free)
		free(to_free);
}
