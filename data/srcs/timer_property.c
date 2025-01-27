/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_property.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:19:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 16:46:46 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	timer_prop_lst_add(t_timer_property *tproperty);
void	add_cell_property(t_data *data, t_timer_property *prop);
void	update_entity_concentration(t_data *data, t_entity *entity,
	t_bool round);

t_timer_property	*new_timer_property(t_property property, t_entity *entity,
	t_entity *caster, t_cell *cell)
{
	t_timer_property	*res;

	if (!entity && (cell && !caster))
		return (NULL);
	res = ft_calloc(sizeof(t_timer_property), 1);
	if (!res)
		return (NULL);
	res->property = property;
	res->entity = entity;
	res->caster = caster;
	res->cell = cell;
	return (res);
}

void	add_timer_property(t_data *data, t_timer_property *tproperty,
	float time, t_bool in_round)
{
	if (!tproperty)
		return ;
	if (tproperty->cell && !tproperty->id_concentration)
		tproperty->id_concentration = -1;
	tproperty->in_round = in_round;
	tproperty->duration = time;
	if (!in_round)
		tproperty->duration = (float)time * 1000000.0;
	timer_prop_lst_add(tproperty);
	if (tproperty->cell)
		add_cell_property(data, tproperty);
	if (tproperty->entity)
		add_prop_refresh(data, tproperty->entity, tproperty->property);
}

void	update_entity_properties(t_data *data, t_entity *entity, t_bool round)
{
	t_list				*lst;
	t_timer_property	*current;

	lst = entity->sheet.timer_property;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (!current->in_round && !round)
			current->duration -= data->frame_time;
		else if (!current->id_concentration && current->in_round && round)
			current->duration--;
		if (current->duration <= 0)
			pop_free_property(data, current);
	}
	update_entity_concentration(data, entity, round);
}

void	clear_entity_timer_prop(t_data *data, t_entity *entity)
{
	t_list				*lst;
	t_timer_property	*current;

	lst = entity->sheet.timer_property;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current)
			pop_free_property(data, current);
	}
	break_concentration(data, entity, 0);
}

void	set_all_entity_timer_prop(t_data *data, t_entity *entity)
{
	t_list				*lst;
	t_timer_property	*current;

	lst = entity->sheet.timer_property;
	while (lst)
	{
		current = lst->content;
		entity->sheet.properties |= current->property;
		lst = lst->next;
	}
	lst = data->current_map->arr[entity->pos.x][entity->pos.y].timer_property;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current)
			entity->sheet.properties |= current->property;
	}
}
