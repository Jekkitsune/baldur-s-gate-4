/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:14:32 by fparis            #+#    #+#             */
/*   Updated: 2025/01/23 00:03:02 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_inlst(t_list *lst, void *check)
{
	t_list	*i;

	i = lst;
	while (i)
	{
		if (i->content == check)
			return (1);
		i = i->next;
	}
	return (0);
}

t_entity	*set_entity_tex(t_entity *entity, t_texture *tex2, t_texture *tex3,
	t_texture *tex4)
{
	entity->tex[1] = tex2;
	entity->tex[2] = tex3;
	entity->tex[3] = tex4;
	return (entity);
}

t_entity	*create_entity(t_data *data, t_vector pos, t_texture *tex)
{
	t_entity	*entity;
	t_list		*new_lst;

	if (pos.x < 0 || pos.x > data->current_map->size.x || pos.y < 0
		|| pos.y > data->current_map->size.y)
		return (NULL);
	entity = ft_calloc(sizeof(t_entity), 1);
	if (!entity)
		return (NULL);
	new_lst = ft_lstnew(entity);
	if (!new_lst)
	{
		free(entity);
		return (NULL);
	}
	entity->size_scale = 1;
	entity->sheet.alive = 1;
	entity->visible = true;
	entity->offset = vecf(0, 0);
	entity->pos = pos;
	entity->tex[0] = tex;
	set_entity_tex(entity, tex, tex, tex);
	ft_lstadd_front(&data->current_map->arr[pos.x][pos.y].entities, new_lst);
	return (entity);
}

void	destroy_inventory(t_data *data, t_entity *entity)
{
	int	i;

	i = 0;
	while (i < INVENTORY_SIZE)
	{
		if (entity->sheet.inventory[i])
			destroy_entity(data, entity->sheet.inventory[i]);
		i++;
	}
}

void	destroy_entity(t_data *data, t_entity *entity)
{
	t_list	*tmp;

	if (!entity)
		return ;
	if (data->player.possession == entity)
		unpossess(data);
	if (data->player.arrow == entity)
		data->player.arrow = NULL;
	destroy_active(data, entity);
	if (in_bound(data->current_map, entity->pos))
	{
		tmp = ft_lstpop(&data->current_map->arr[entity->pos.x][entity->pos.y].\
		entities, entity);
		if (tmp)
			free(tmp);
	}
	destroy_inventory(data, entity);
	free_path(&entity->behavior.path);
	leave_combat(data, entity);
	leave_party(data, entity);
	clear_entity_timer_prop(data, entity);
	clear_entity_timer_effect(data, entity);
	free(entity->sheet.name);
	ft_free_tab(entity->dialog.dialog_tab);
	free(entity);
}
