/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_property.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:19:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/06 06:11:22 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_timer_property	*new_timer_property(t_property property, t_entity *entity)
{
	t_timer_property	*res;

	res = ft_calloc(sizeof(t_timer_property), 1);
	if (!res)
		return (NULL);
	res->property = property;
	res->entity = entity;
	entity->sheet.properties = entity->sheet.properties | property;
	return (res);
}

void	add_timer_property(t_data *data, t_timer_property *tproperty, float time, t_bool in_round)
{
	t_list			*new;

	if (!tproperty)
		return ;
	new = ft_lstnew(tproperty);
	if (!new)
	{
		tproperty->entity->sheet.properties &= ~tproperty->property;
		free(tproperty);
		return ;
	}
	tproperty->in_round = in_round;
	tproperty->duration = time;
	if (!in_round)
		tproperty->duration = (float)time * 1000000.0;
	ft_lstadd_front(&data->timer_property, new);
}

void	update_all_timer_properties(t_data *data, t_bool round)
{
	t_list				*lst;
	t_list				*tmp;
	t_timer_property	*current;

	lst = data->timer_property;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current && (round && current->in_round && --current->duration <= 0)
			|| (!current->in_round && (current->duration -= data->frame_time) <= 0))
		{
			current->entity->sheet.properties &= ~current->property;
			tmp = ft_lstpop(&data->timer_property, current);
			free(tmp->content);
			free(tmp);
		}
	}
}

void	clear_entity_timer_prop(t_data *data, t_entity *entity)
{
	t_list				*lst;
	t_list				*tmp;
	t_timer_property	*current;

	lst = data->timer_property;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current && current->entity == entity)
		{
			current->entity->sheet.properties &= ~current->property;
			tmp = ft_lstpop(&data->timer_property, current);
			free(tmp->content);
			free(tmp);
		}
	}
}

void	set_all_entity_timer_prop(t_data *data, t_entity *entity)
{
	t_list				*lst;
	t_timer_property	*current;

	lst = data->timer_property;
	while (lst)
	{
		current = lst->content;
		if (current && current->entity == entity)
			current->entity->sheet.properties |= current->property;
		lst = lst->next;
	}
}
