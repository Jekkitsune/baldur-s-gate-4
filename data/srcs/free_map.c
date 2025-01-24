/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:09:43 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 13:53:31 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_actives(t_data *data, t_map *map)
{
	t_list	*lst;
	t_list	*tmp;

	lst = map->active_entities;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		destroy_entity(data, tmp->content);
	}
}

void	free_cell(t_data *data, t_cell *cell)
{
	t_list	*lst;
	t_list	*tmp;

	lst = cell->entities;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		destroy_entity(data, tmp->content);
	}
	lst = cell->timer_property;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	free_map(t_data *data, t_map *map)
{
	int		x;
	int		y;

	data->current_map = map;
	free_map_actives(data, map);
	x = -1;
	while (++x < map->size.x)
	{
		y = -1;
		while (++y < map->size.y)
			free_cell(data, &map->arr[x][y]);
		free(map->arr[x]);
	}
	free(map->arr);
	free(map->path);
	free(map);
}

void	free_all_maps(t_data *data)
{
	t_list	*lst;
	t_list	*to_free;

	lst = data->map_list;
	while (lst)
	{
		free_map(data, lst->content);
		to_free = lst;
		lst = lst->next;
		free(to_free);
	}
}
