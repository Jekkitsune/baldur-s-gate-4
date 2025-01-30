/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_property_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:33:44 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 12:06:05 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	try_resist_spell(t_data *data, t_entity *entity, t_property prop,
	int stat);

void	add_cell_property(t_data *data, t_timer_property *prop)
{
	t_list	*entity_lst;

	entity_lst = prop->cell->entities;
	while (entity_lst)
	{
		add_prop_refresh(data, entity_lst->content, prop->property);
		entity_lst = entity_lst->next;
	}
}

void	timer_prop_lst_add(t_timer_property *p)
{
	t_list	*list_entity;
	t_list	*list_caster;
	t_list	*list_cell;

	list_entity = NULL;
	list_caster = NULL;
	list_cell = NULL;
	if (p->entity)
		list_entity = ft_lstnew(p);
	if (p->caster)
		list_caster = ft_lstnew(p);
	if (p->cell)
		list_cell = ft_lstnew(p);
	if ((p->entity && !list_entity) || (p->caster && !list_caster)
		|| (p->cell && !list_cell))
	{
		free(list_entity);
		free(list_caster);
		free(list_cell);
		free(p);
		return ;
	}
	ft_lstadd_front(&p->entity->sheet.timer_property, list_entity);
	ft_lstadd_front(&p->caster->sheet.timer_concentration, list_caster);
	ft_lstadd_front(&p->cell->timer_property, list_cell);
}

t_bool	remove_specific_prop(t_data *data, t_entity *entity,
	t_property property)
{
	t_list				*lst;
	t_timer_property	*current;

	lst = entity->sheet.timer_property;
	while (lst)
	{
		current = lst->content;
		if (current && check_properties(current->property, property))
		{
			pop_free_property(data, current);
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}

void	update_entity_concentration(t_data *data, t_entity *entity,
	t_bool round)
{
	t_list				*lst;
	t_timer_property	*current;

	lst = entity->sheet.timer_concentration;
	while (lst)
	{
		current = lst->content;
		if (current->cell && current->color)
		{
			if (!current->cell->fog_color)
				current->cell->fog_color = current->color;
			else
				current->cell->fog_color
					= average_filter(current->cell->fog_color, current->color);
		}
		lst = lst->next;
		if (round)
		{
			current->duration--;
			if (current->duration <= 0)
				pop_free_property(data, current);
		}
	}
}

void	start_turn_effect(t_data *data, t_entity *entity)
{
	if (!entity || !data)
		return ;
	if (entity->sheet.properties & acid_puddle_prop)
		acid_puddle_dmg(data, entity);
	if (entity->sheet.properties & hunger_of_hadar_prop)
		hunger_of_hadar_dmg(data, entity);
	if (entity->sheet.properties & webbed)
		web_effect(data, entity);
	try_resist_spell(data, entity, paralyzed, WIS);
	if (entity->sheet.properties & (banished | paralyzed | hypnotized
		| stunned))
		next_turn(data);
	if (entity->sheet.properties & haste)
		entity->sheet.action++;
}
