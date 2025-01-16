/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:51:26 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 01:04:39 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_borders(t_data *data, t_vector start);

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

int	get_inv_index(int button_size, t_vector pos, t_vector mouse)
{
	int	res;

	res = (mouse.x - pos.x) / button_size;
	res += 2 * ((mouse.y - pos.y) / button_size);
	return (res);
}

int	inventory_hover_index(t_data *data)
{
	t_vector	mouse;
	t_vector	pos;
	int			width;
	int			length;

	if (!data->player.possession
		|| !data->player.possession->sheet.inventory_open)
		return (-1);
	width = data->button_scale_size * 2;
	length = (INVENTORY_SIZE / 2) * data->button_scale_size;
	pos.x = data->win_size.x - width - 10;
	pos.y = (data->win_size.y / 2) - (length / 2) - data->button_scale_size / 2;
	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (mouse.x >= pos.x && mouse.x < data->win_size.x - 10
		&& mouse.y >= pos.y && mouse.y < pos.y
		+ (data->button_scale_size * (NON_EQUIP / 2)))
		return (get_inv_index(data->button_scale_size, pos, mouse));
	pos.y += data->button_scale_size / 2;
	if (mouse.x >= pos.x && mouse.x < data->win_size.x - 10
		&& mouse.y >= pos.y + (data->button_scale_size * (NON_EQUIP / 2))
		&& mouse.y < pos.y + (data->button_scale_size * (INVENTORY_SIZE / 2)))
		return (get_inv_index(data->button_scale_size, pos, mouse));
	return (-1);
}

int	can_move_inventory(t_entity *inventory[INVENTORY_SIZE], t_entity *to_move,
	int pos)
{
	t_type	type;

	if (!to_move)
		return (true);
	type = to_move->sheet.type;
	if (pos < NON_EQUIP)
	{
		if (pos == weapon_1 && inventory[weapon_2] && type != weapon_2)
			return (false);
		if (pos == weapon_1 && type == weapon_2)
			return (true);
		return (pos == (int)type);
	}
	return (pos < INVENTORY_SIZE);
}

void	inventory_swap(t_data *data, t_entity *entity, int index1, int index2)
{
	t_entity	*tmp;
	t_entity	**inventory;

	inventory = entity->sheet.inventory;
	if (!entity || index1 < 0 || index1 >= INVENTORY_SIZE || index2 < 0
		|| index2 >= INVENTORY_SIZE || index1 == index2)
		return ;
	if (can_move_inventory(inventory, inventory[index1], index2)
		&& can_move_inventory(inventory, inventory[index2], index1))
	{
		tmp = inventory[index1];
		inventory[index1] = inventory[index2];
		inventory[index2] = tmp;
		if (index1 < NON_EQUIP || index2 < NON_EQUIP)
			refresh_stats(data, entity);
	}
}
