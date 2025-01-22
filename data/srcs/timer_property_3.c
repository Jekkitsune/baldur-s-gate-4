/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_property_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:33:44 by fparis            #+#    #+#             */
/*   Updated: 2025/01/22 08:50:03 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_cell_property(t_timer_property *prop)
{
	t_list	*entity_lst;

	entity_lst = prop->cell->entities;
	while (entity_lst)
	{
		((t_entity *)entity_lst->content)->sheet.properties |= prop->property;
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
