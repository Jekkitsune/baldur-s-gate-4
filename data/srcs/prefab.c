/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:10:07 by fparis            #+#    #+#             */
/*   Updated: 2025/01/25 04:04:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	*refresh_spawned(t_data *data, t_entity *entity, char *name)
{
	t_list		*new_lst;
	t_vector	pos;

	pos = entity->pos;
	new_lst = ft_lstnew(entity);
	if (!new_lst)
	{
		free(entity);
		free(name);
		return (NULL);
	}
	entity->visible = true;
	ft_lstadd_front(&data->current_map->arr[pos.x][pos.y].entities, new_lst);
	entity->sheet.name = name;
	change_anim(entity, "idle", true);
	long_rest(data, entity);
	round_refresh_stat(entity);
	return (entity);
}

t_entity	*spawn_entity(t_data *data, t_entity *prefab, t_vector pos,
	char *name)
{
	t_entity	*entity;

	if (!prefab || pos.x < 0 || pos.x >= data->current_map->size.x || pos.y < 0
		|| pos.y >= data->current_map->size.y)
	{
		free(name);
		return (NULL);
	}
	entity = ft_calloc(sizeof(t_entity), 1);
	if (!entity)
	{
		free(name);
		return (NULL);
	}
	ft_memcpy(entity, prefab, sizeof(t_entity));
	entity->pos = pos;
	entity->sheet.prefab = prefab;
	return (refresh_spawned(data, entity, name));
}

void	add_prefab(t_data *data, t_entity *prefab, char *name)
{
	t_entity	**res;

	if (!prefab)
		return ;
	prefab->sheet.name = name;
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

t_entity	*get_prefab(t_data *data, char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (NULL);
	while (i < data->nb_prefab)
	{
		if (!ft_strcmp(data->prefab_tab[i]->sheet.name, name))
			return (data->prefab_tab[i]);
		i++;
	}
	return (NULL);
}
