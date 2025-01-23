/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_active.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:24:17 by fparis            #+#    #+#             */
/*   Updated: 2025/01/23 00:00:27 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_entity	*add_active(t_data *data, t_entity *entity,
	void (*behavior)(void *, void *))
{
	t_list			*new_lst;
	struct timeval	tv;

	if (!entity)
		return (NULL);
	new_lst = ft_lstnew(entity);
	if (!new_lst)
	{
		destroy_entity(data, entity);
		return (NULL);
	}
	new_lst->content = entity;
	entity->behavior.func = behavior;
	entity->active = 1;
	gettimeofday(&tv, NULL);
	entity->behavior.start_time = tv.tv_sec;
	ft_lstadd_back(&data->current_map->active_entities, new_lst);
	return (entity);
}

void	remove_active(t_data *data, t_entity *entity)
{
	t_list	*to_free;
	t_map	*map;

	map = data->current_map;
	entity->active = 0;
	if (in_bound(map, entity->pos))
	{
		if (ft_inlst(map->arr[entity->pos.x][entity->pos.y].entities, entity))
		{
			to_free = ft_lstpop(&map->active_entities, entity);
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

	if (!entity->active)
		return ;
	to_free = ft_lstpop(&data->current_map->active_entities, entity);
	if (to_free)
		free(to_free);
}
