/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:51:26 by fparis            #+#    #+#             */
/*   Updated: 2024/12/16 23:33:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_borders(t_data *data, t_vector start);
void	draw_hover(t_data *data, t_vector start, uint32_t color);

int	inventory_hover_index(t_data *data)
{
	t_vector	mouse_pos;
	t_vector	start;
	int			width;
	int			length;
	int			res;

	if (!data->player.possession || !data->player.possession->sheet.inventory_open)
		return (-1);
	width = data->button_scale_size * 2;
	length = (INVENTORY_SIZE / 2) * data->button_scale_size;
	start.x = data->win_size.x - width - 10;
	start.y = (data->win_size.y / 2) - (length / 2) - data->button_scale_size / 2;
	mlx_mouse_get_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x >= start.x && mouse_pos.x < data->win_size.x - 10
		&& mouse_pos.y >= start.y && mouse_pos.y < start.y + (data->button_scale_size * (NON_EQUIP / 2)))
	{
		res = (mouse_pos.x - start.x) / data->button_scale_size;
		res += 2 * ((mouse_pos.y - start.y) / data->button_scale_size);
		return (res);
	}
	start.y += data->button_scale_size / 2;
	if (mouse_pos.x >= start.x && mouse_pos.x < data->win_size.x - 10
		&& mouse_pos.y >= start.y + (data->button_scale_size * (NON_EQUIP / 2))
		&& mouse_pos.y < start.y + (data->button_scale_size * (INVENTORY_SIZE / 2)))
	{
		res = (mouse_pos.x - start.x) / data->button_scale_size;
		res += 2 * ((mouse_pos.y - start.y) / data->button_scale_size);
		return (res);
	}
	return (-1);
}

void	draw_inventory_img(t_data *data, t_entity *entity, t_vector start)
{
	if (entity && entity->sheet.portrait)
		show_tex(data, entity->sheet.portrait, start);
}

void	draw_equip(t_data *data, t_entity *inventory[INVENTORY_SIZE], t_vector start, int hover_index)
{
	t_vector	current;
	int			i;

	i = 0;
	while (i < NON_EQUIP)
	{
		current.x = start.x + ((i % 2) * data->button_scale_size);
		current.y = start.y + ((i / 2) * data->button_scale_size);
		draw_borders(data, current);
		draw_hover(data, current, 0xDD6B5333);
		draw_inventory_img(data, inventory[i], current);
		i++;
	}
	if (hover_index < 0 || hover_index >= NON_EQUIP)
		return ;
	current.x = start.x + ((hover_index % 2) * data->button_scale_size);
	current.y = start.y + ((hover_index / 2) * data->button_scale_size);
	if (data->player.mouse_button[0])
		draw_hover(data, current, 0x88000000);
	else
		draw_hover(data, current, 0x44000000);
}

void	draw_unequip(t_data *data, t_entity *inventory[INVENTORY_SIZE], t_vector start, int hover_index)
{
	t_vector	current;
	int			i;

	start.y += data->button_scale_size / 2;
	i = NON_EQUIP;
	while (i < INVENTORY_SIZE)
	{
		current.x = start.x + ((i % 2) * data->button_scale_size);
		current.y = start.y + ((i / 2) * data->button_scale_size);
		draw_borders(data, current);
		draw_hover(data, current, 0xDD6B5333);
		draw_inventory_img(data, inventory[i], current);
		i++;
	}
	if (hover_index < NON_EQUIP || hover_index >= INVENTORY_SIZE)
		return ;
	current.x = start.x + ((hover_index % 2) * data->button_scale_size);
	current.y = start.y + ((hover_index / 2) * data->button_scale_size);
	if (data->player.mouse_button[0])
		draw_hover(data, current, 0x88000000);
	else
		draw_hover(data, current, 0x44000000);
}

void	draw_inventory(t_data *data, t_entity *inventory[INVENTORY_SIZE])
{
	int			width;
	int			length;
	int			hover_index;
	t_vector	start;

	width = data->button_scale_size * 2;
	length = (INVENTORY_SIZE / 2) * data->button_scale_size;
	start.x = data->win_size.x - width - 10;
	start.y = (data->win_size.y / 2) - (length / 2) - data->button_scale_size / 2;
	hover_index = inventory_hover_index(data);
	draw_equip(data, inventory, start, hover_index);
	draw_unequip(data, inventory, start, hover_index);
	if (data->player.active_button && data->player.possession
		&& &data->player.possession->sheet.inventory_button == data->player.active_button
		&& data->player.active_button->active > 0)
	{
		if (data->player.active_button->active - 1 >= NON_EQUIP)
			start.y += data->button_scale_size / 2;
		start.x = start.x + (((data->player.active_button->active - 1) % 2) * data->button_scale_size);
		start.y = start.y + (((data->player.active_button->active - 1) / 2) * data->button_scale_size);
		draw_hover(data, start, 0xAA000000);
	}
}

int	can_move_inventory(t_entity *inventory[INVENTORY_SIZE], t_entity *to_move, int pos)
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
		return (pos == type);
	}
	return (pos < INVENTORY_SIZE);
}

void	inventory_swap(t_entity *entity, t_entity *inventory[INVENTORY_SIZE], int index1, int index2)
{
	t_entity	*tmp;

	if (!entity || index1 < 0 || index1 >= INVENTORY_SIZE || index2 < 0 || index2 >= INVENTORY_SIZE || index1 == index2)
		return ;
	if (can_move_inventory(inventory, inventory[index1], index2) && can_move_inventory(inventory, inventory[index2], index1))
	{
		tmp = inventory[index1];
		inventory[index1] = inventory[index2];
		inventory[index2] = tmp;
	}
	refresh_stat(entity);
}
