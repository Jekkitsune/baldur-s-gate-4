/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_button_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:50:43 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:08:14 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_button_lst(t_data *data)
{
	t_button_lst	*to_free;

	while (data->button_lst)
	{
		to_free = data->button_lst;
		data->button_lst = data->button_lst->next;
		free(to_free);
	}
}

void	add_button_lst(t_data *data, char *name,
	void (*button_init)(t_data *data, t_button *button))
{
	t_button_lst	*new;

	if (!name || !button_init)
		return ;
	new = ft_calloc(sizeof(t_button_lst), 1);
	if (!new)
		return ;
	new->name = name;
	new->button_init = button_init;
	if (!data->button_lst)
		data->button_lst = new;
	else
	{
		new->next = data->button_lst;
		data->button_lst = new;
	}
}

void	(*get_button(t_data *data, char *name))(t_data *data, t_button *button)
{
	t_button_lst	*lst;

	lst = data->button_lst;
	while (lst)
	{
		if (!ft_strcmp(lst->name, name))
			return (lst->button_init);
		lst = lst->next;
	}
	return (NULL);
}

void	init_button_lst(t_data *data)
{
	add_button_lst(data, "Check", init_check_button);
	add_button_lst(data, "Move", init_move_button);
	add_button_lst(data, "Interact", init_interact_button);
	add_button_lst(data, "Inventory", init_inventory_button);
	add_button_lst(data, "Fireball", init_fireball_button);
	add_button_lst(data, "Rage", init_rage_button);
	add_button_lst(data, "Healing potion", init_heal_potion_button);
	add_button_lst(data, "Greater healing potion",
		init_greater_heal_potion_button);
	add_button_lst(data, "Speed potion", init_speed_potion_button);
	add_button_lst(data, "Enlarge potion", init_enlarge_potion_button);
	add_button_lst(data, "Dash bonus", init_dash_bonus_button);
}
