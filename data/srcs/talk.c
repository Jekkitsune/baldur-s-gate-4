/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:59:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/23 09:58:35 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_entity_dialog(t_entity *entity, char *str)
{
	char	**tab;

	if (!entity || !str)
		return ;
	tab = ft_split(str, '\\');
	if (!tab)
		return ;
	if (entity->dialog.dialog_tab)
		ft_free_tab(entity->dialog.dialog_tab);
	entity->dialog.dialog_size = ft_tablen(tab);
	entity->dialog.dialog_i = 0;
	entity->dialog.dialog_tab = tab;
	entity->dialog.is_talking = 0;
}

void	engage_next_dialog(t_data *data, t_entity *entity)
{
	t_spellinfo	info;

	ft_bzero(&info, sizeof(t_spellinfo));
	info.effect = talk;
	info.target = entity;
	add_timer_effect(data, info, 5, false);
}

void	stop_next_dialog(t_data *data, t_entity *entity)
{
	t_list			*lst;
	t_list			*tmp;
	t_timer_effect	*current;

	lst = data->timer_effect;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current && current->spell.effect == talk
			&& current->spell.target == entity)
		{
			tmp = ft_lstpop(&data->timer_effect, current);
			free(tmp->content);
			free(tmp);
		}
	}
}

void	talk(void *data_param, void *spell_param)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = ((t_spellinfo *)spell_param)->target;
	if (!entity || !entity->sheet.alive || !entity->dialog.dialog_tab)
		return ;
	if (!entity->dialog.is_talking)
	{
		entity->dialog.is_talking = true;
		entity->dialog.dialog_i = -1;
	}
	else if (((t_spellinfo *)spell_param)->caster)
		stop_next_dialog(data, entity);
	if (entity->dialog.dialog_i >= entity->dialog.dialog_size - 1)
	{
		entity->dialog.is_talking = false;
		return ;
	}
	entity->dialog.dialog_i++;
	show_info(data, "%s: \"%s\"", entity->sheet.name,
		entity->dialog.dialog_tab[entity->dialog.dialog_i]);
	engage_next_dialog(data, entity);
}
