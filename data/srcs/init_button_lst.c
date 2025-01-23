/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_button_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:50:43 by fparis            #+#    #+#             */
/*   Updated: 2025/01/22 23:53:09 by fparis           ###   ########.fr       */
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
		printf(":%s: and :%s:\n", lst->name, name);
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
}
