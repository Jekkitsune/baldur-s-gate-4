/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:10:07 by fparis            #+#    #+#             */
/*   Updated: 2024/11/20 22:17:09 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	*spawn_entity(t_data *data, t_entity *prefab, t_vector pos)
{
	t_entity	*entity;
	t_list		*new_lst;

	if (pos.x < 0 || pos.x > data->current_map->size.x || pos.y < 0
		|| pos.y > data->current_map->size.y)
		return (NULL);
	entity = ft_calloc(sizeof(t_entity), 1);
	if (!entity)
		return (NULL);
	ft_memcpy(entity, prefab, sizeof(t_entity));
	new_lst = ft_lstnew(entity);
	if (!new_lst)
	{
		free(entity);
		return (NULL);
	}
	entity->pos = pos;
	entity->visible = true;
	ft_lstadd_front(&data->current_map->arr[pos.x][pos.y].entities, new_lst);
	return (entity);
}

void	add_prefab(t_data *data, t_entity *prefab)
{
	t_entity	**res;

	if (!prefab)
		return ;
	if (!data->prefab_tab)
	{
		data->prefab_tab = ft_calloc(1, sizeof(t_entity *));
		if (!data->prefab_tab)
		{
			free_prefab_entity(data, prefab);
			return ;
		}
		data->nb_prefab = 1;
		data->prefab_tab[0] = prefab;
		return ;
	}
	res = ft_calloc(data->nb_prefab + 1, sizeof(t_entity *));
	if (!res)
		return ;
	ft_memcpy(res, data->prefab_tab, data->nb_prefab * sizeof(t_entity *));
	res[data->nb_prefab] = prefab;
	free(data->prefab_tab);
	data->nb_prefab += 1;
	data->prefab_tab = res;
}
