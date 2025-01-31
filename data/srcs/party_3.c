/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 04:51:18 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 10:05:17 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	join_party(t_data *data, t_entity *entity)
{
	if (!entity || in_party(data, entity))
		return ;
	possess_control(entity, true);
	if (!entity->active)
		add_active(data, entity, NULL);
	ft_lstadd_front(&data->round_manager.party, ft_lstnew(entity));
}

t_entity	*in_party_name(t_data *data, char *name)
{
	t_list		*lst;
	t_entity	*current;

	lst = data->round_manager.party;
	while (lst)
	{
		current = lst->content;
		if (current && !ft_strcmp(current->sheet.name, name))
			return (current);
		lst = lst->next;
	}
	return (NULL);
}

void	check_party_exp(t_data *data)
{
	while (data->round_manager.party_exp >= 100)
	{
		data->round_manager.party_exp -= 100;
		level_up_party(data);
	}
}
