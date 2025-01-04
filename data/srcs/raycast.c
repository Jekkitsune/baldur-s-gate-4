/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:33:20 by fparis            #+#    #+#             */
/*   Updated: 2025/01/04 02:17:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_entity(t_data *data, t_entity *entity)
{
	t_list		*i;
	t_list		*new;
	t_entity	compare;

	new = ft_lstnew(entity);
	if (!new)
		return ; //exit free pt ???
	calculate_entity_info(data, entity);
	entity->nb_impact++;
	i = data->player.visible_entities;
	if (!i || ((t_entity *)i->content)->distance <= entity->distance)
	{
		ft_lstadd_front(&data->player.visible_entities, new);
		return ;
	}
	while (i->next && ((t_entity *)i->next->content)->distance > entity->distance)
		i = i->next;
	new->next = i->next;
	i->next = new;
}

void	add_cell_entities(t_data *data, t_impact *ray)
{
	t_list		*cell_lst;
	t_entity	*current_entity;

	cell_lst = data->current_map->arr[ray->wall_pos.x][ray->wall_pos.y].entities;
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

t_impact	*check_wall(t_impact *impact, t_data *data, t_vectorf length, t_vectorf slope_coeff, t_vector sign)
{
	int	tmp;

	if (!in_bound(data->current_map, impact->wall_pos)
		|| ft_min(ft_absf(length.x), ft_absf(length.y)) > data->render_distance)
			return (impact);
	if (!length.x || !length.y)
		return (NULL);
	if (data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y].type != WALL
		&& data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y].type != DOOR)
	{
		add_cell_entities(data, impact);
		return (NULL);
	}
	impact->cell = &data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y];
	if (impact->cell->type == DOOR)
	{
		if (ft_absf(length.x) > ft_absf(length.y))
		{
			tmp = impact->wall_pos.y;
			length.y += 0.5 * slope_coeff.y;
			if (length.y / slope_coeff.y != impact->wall_pos.y)
				impact->wall_pos.y += sign.y;
			if ((data->player.pos.x * (data->scale * 2) + data->player.offset.x + data->scale + (impact->direc.x * ft_absf(length.y))) / 20 - impact->wall_pos.x
				> data->current_map->arr[impact->wall_pos.x][tmp].timer)
			{
				impact->wall_pos.y = tmp;
				return (NULL);
			}
		}
		else
		{
			tmp = impact->wall_pos.x;
			length.x += 0.5 * slope_coeff.x;
			if (length.x / slope_coeff.x != impact->wall_pos.x)
				impact->wall_pos.x += sign.x;
			if ((data->player.pos.y * (data->scale * 2) + data->player.offset.y + data->scale + (impact->direc.y * ft_absf(length.x))) / 20 - impact->wall_pos.y
				> data->current_map->arr[tmp][impact->wall_pos.y].timer)
			{
				impact->wall_pos.x = tmp;
				return (NULL);
			}
		}
	}
	if (ft_absf(length.x) <= ft_absf(length.y))
	{
		impact->face = 2;
		if (length.x < 0)
			impact->face = 4;
		impact->length = ft_absf(length.x);
	}
	else
	{
		impact->face = 1;
		if (length.y < 0)
			impact->face = 3;
		impact->length = ft_absf(length.y);
	}
	return (impact);
}

void		free_visible_lst(t_data *data)
{
	t_list	*i;
	t_list	*to_free;

	if (!data->player.visible_entities)
		return ;
	i = data->player.visible_entities;
	while (i)
	{
		to_free = i;
		i = i->next;
		free(to_free);
	}
	data->player.visible_entities = NULL;
}

t_impact	raycast(t_vector start, t_vectorf direc, t_data *data, t_vectorf slope_coef)
{
	t_vector	sign;
	t_vectorf	length;
	t_impact	impact;

	//free_visible_lst(data);
	impact.face = 0;
	impact.length = 0;
	impact.direc.x = direc.x;
	impact.direc.y = direc.y;
	if (direc.x < 0)
	{
		sign.x = -1;
		length.x = (float)((data->player.offset.x + data->scale) / (float)(data->scale * 2)) * slope_coef.x * sign.x;
	}
	else
	{
		sign.x = 1;
		length.x = ((float)(1 - ((float)(data->player.offset.x + data->scale)) / (float)(data->scale * 2))) * slope_coef.x;
	}
	if (direc.y < 0)
	{
		sign.y = -1;
		length.y = (float)((data->player.offset.y + data->scale) / (float)(data->scale * 2)) * slope_coef.y * sign.y;
	}
	else
	{
		sign.y = 1;
		length.y = ((float)(1 - ((float)(data->player.offset.y + data->scale)) / (float)(data->scale * 2))) * slope_coef.y;
	}
	slope_coef.x *= sign.x;
	slope_coef.y *= sign.y;
	impact.wall_pos.x = start.x;
	impact.wall_pos.y = start.y;
	while (ft_absf(length.x) < data->render_distance || ft_absf(length.y) < data->render_distance)
	{
		while (ft_absf(length.x) <= ft_absf(length.y))
		{
			impact.wall_pos.x += sign.x;
			if (check_wall(&impact, data, length, slope_coef, sign))
				return (impact);
			length.x += slope_coef.x;
		}
		while (ft_absf(length.y) <= ft_absf(length.x))
		{
			impact.wall_pos.y += sign.y;
			if (check_wall(&impact, data, length, slope_coef, sign))
				return (impact);
			length.y += slope_coef.y;
		}
	}
	impact.face = 0;
	impact.length = data->render_distance;
	return (impact);
}

t_impact	get_impact(t_vector start, t_vectorf direc, t_data *data)
{
	t_vectorf	delta;
	t_vectorf	slope_coef;

	delta.x = ft_absf(direc.x * 100);
	delta.y = ft_absf(direc.y * 100);
	slope_coef.x = data->scale * 2;
	slope_coef.y = data->scale * 2;
	if (delta.x != 0)
		slope_coef.x = fabs((double)(data->scale * 2) / direc.x);
		//slope_coef.x = sqrt(pow(data->scale * 2, 2) + pow(delta.y / delta.x * (data->scale * 2), 2));
	if (delta.y != 0)
		slope_coef.y = fabs((double)(data->scale * 2) / direc.y);
		//slope_coef.y = sqrt(pow(data->scale * 2, 2) + pow(delta.x / delta.y * (data->scale * 2), 2));
	return (raycast(start, direc, data, slope_coef));
}
