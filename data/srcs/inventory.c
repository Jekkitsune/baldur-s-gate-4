/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:40:54 by fparis            #+#    #+#             */
/*   Updated: 2024/12/13 18:38:14 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_be_taken(t_entity *taker, t_entity *taken)
{
	int	i;

	if (taker->sheet.weight + taken->sheet.weight > taker->sheet.carry
		|| taker == taken)
		return (-1);
	if (taken->sheet.type < NON_EQUIP)
	{
		if (taken->sheet.type == weapon_2 && !taker->sheet.inventory[weapon_1])
			return (weapon_1);
		else if (!taker->sheet.inventory[taken->sheet.type])
			return (taken->sheet.type);
	}
	i = NON_EQUIP;
	while (i < INVENTORY_SIZE)
	{
		if (!taker->sheet.inventory[i])
			return (i);
		i++;
	}
	return (-1);
}

t_bool	add_to_inventory(t_data *data, t_entity *taker, t_entity *taken)
{
	int	i;

	if (!taker || !taken)
		return (false);
	i = can_be_taken(taker, taken);
	if (i != -1 && taken->active)
		free(ft_lstpop(&data->current_map->active_entities, taken));
	if (i != -1 && i < INVENTORY_SIZE && !taker->sheet.inventory[i])
	{
		if (in_bound(*data->current_map, taken->pos))
			free(ft_lstpop(&data->current_map->arr[taken->pos.x][taken->pos.y].entities, taken));
		taker->sheet.inventory[i] = taken;
		return (true);
	}
	return (false);
}

void	take(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;
	t_vector	pos;

	data = data_param;
	entity = entity_param;
	if (!data->player.arrow)
		select_target(data);
	if (!check_dist_obstacle(data, entity, spell.range, spell.visible_target)
		|| !confirm(data->player.active_button))
		return ;
	pos = data->player.arrow->pos;
	spell.target = cycle_entity_cell(data, 0);
	remove_selector(data);
	if (spell.target && spell.target->visible)
	{
		if (add_to_inventory(data, entity, spell.target))
			printf("%s picked up %s.\n", entity->sheet.name, spell.target->sheet.name);
		return ;
		printf("%s tried to pick up %s, but couldn't.\n", entity->sheet.name, spell.target->sheet.name);
	}
}

void	init_take_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 0;
	button->spellinfo.range = 1;
	button->spellinfo.visible_target = false;
	button->func = NULL;
	button->img = get_tex(data, "take_button");
	button->func = take;
}

void	open_inventory(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = entity_param;
	remove_selector(data);
	entity->sheet.inventory_open = !entity->sheet.inventory_open;
}

void	init_inventory_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 0;
	button->spellinfo.range = 0;
	button->spellinfo.visible_target = false;
	button->func = NULL;
	button->img = get_tex(data, "inventory_button");
	button->func = open_inventory;
}
