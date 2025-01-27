/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:00:57 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 13:32:13 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_impact	*check_door_y(t_impact *impact, t_data *data, t_vectorf length,
	t_vector sign)
{
	int	tmp;

	tmp = impact->wall_pos.y;
	length.y += 0.5 * impact->slope_coef.y;
	if (length.y / impact->slope_coef.y != impact->wall_pos.y)
		impact->wall_pos.y += sign.y;
	if ((data->player.pos.x * (data->scale * 2) + data->player.offset.x
			+ data->scale + (impact->direc.x * ft_absf(length.y)))
		/ (data->scale * 2) - impact->wall_pos.x
		> data->current_map->arr[impact->wall_pos.x][tmp].timer)
	{
		impact->wall_pos.y = tmp;
		return (NULL);
	}
	return (found_wall(impact, length));
}

t_impact	*check_door(t_impact *impact, t_data *data, t_vectorf length,
	t_vector sign)
{
	int	tmp;

	if (ft_absf(length.x) > ft_absf(length.y))
		return (check_door_y(impact, data, length, sign));
	else
	{
		tmp = impact->wall_pos.x;
		length.x += 0.5 * impact->slope_coef.x;
		if (length.x / impact->slope_coef.x != impact->wall_pos.x)
			impact->wall_pos.x += sign.x;
		if ((data->player.pos.y * (data->scale * 2) + data->player.offset.y
				+ data->scale + (impact->direc.y * ft_absf(length.x)))
			/ (data->scale * 2) - impact->wall_pos.y
			> data->current_map->arr[tmp][impact->wall_pos.y].timer)
		{
			impact->wall_pos.x = tmp;
			return (NULL);
		}
	}
	return (found_wall(impact, length));
}

void	free_visible_lst(t_data *data)
{
	t_list	*i;
	t_list	*to_free;
	t_fog	*fog_i;
	t_fog	*fog_free;

	i = data->player.visible_entities;
	while (i)
	{
		to_free = i;
		i = i->next;
		free(to_free);
	}
	data->player.visible_entities = NULL;
	fog_i = data->player.visible_fog;
	while (i)
	{
		fog_free = fog_i;
		fog_i = fog_i->next;
		free(fog_free);
	}
	data->player.visible_fog = NULL;
}

void	sort_entity(t_data *data, t_entity *entity)
{
	t_list		*i;
	t_list		*new;

	new = ft_lstnew(entity);
	if (!new)
		return ;
	calculate_entity_info(data, entity);
	entity->nb_impact++;
	i = data->player.visible_entities;
	if (!i || ((t_entity *)i->content)->distance <= entity->distance)
	{
		ft_lstadd_front(&data->player.visible_entities, new);
		return ;
	}
	while (i->next && ((t_entity *)i->next->content)->distance
		> entity->distance)
		i = i->next;
	new->next = i->next;
	i->next = new;
}

void	add_cell_entities(t_data *data, t_impact *ray)
{
	t_list		*cell_lst;
	t_entity	*current_entity;

	cell_lst = data->current_map->arr[ray->wall_pos.x][ray->wall_pos.y].\
	entities;
	while (cell_lst)
	{
		current_entity = cell_lst->content;
		if (current_entity->nb_impact > 0)
			return ;
		if (current_entity->visible)
			sort_entity(data, current_entity);
		cell_lst = cell_lst->next;
	}
}
