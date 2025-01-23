/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_draw_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 00:55:19 by fparis            #+#    #+#             */
/*   Updated: 2025/01/23 10:59:35 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_inventory_img(t_data *data, t_entity *entity, t_vector start);
void	show_price(t_data *data, int price, t_vector pos);
void	draw_gold_button(t_data *data, t_vector inventory_start);

void	draw_equip(t_data *data, t_entity *inventory[INVENTORY_SIZE],
	t_vector start, int hover_index)
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

void	draw_unequip(t_data *data, t_entity *inventory[INVENTORY_SIZE],
	t_vector start, int hover_index)
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

void	draw_invbutton_name(t_data *data, t_entity *inventory[INVENTORY_SIZE],
	int index)
{
	t_vector	mouse_pos;
	t_vector	pos;
	t_strput	*to_put;

	if (index < 0 || !inventory[index] || !inventory[index]->sheet.name)
		return ;
	mlx_mouse_get_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	pos = vec(mouse_pos.x - 5, mouse_pos.y - 10);
	to_put = strput(ft_strdup(inventory[index]->sheet.name),
			pos, 20, 0xFF000000);
	screen_string_put(data, to_put, 0);
	if (data->player.description_mode && inventory[index]->sheet.description)
	{
		pos.y -= 10;
		to_put = strput(ft_strdup(inventory[index]->sheet.description),
				pos, 20, 0xFF000000);
		screen_string_put(data, to_put, 0);
	}
	if (!data->player.shop_mode)
		return ;
	pos.y -= 10;
	show_price(data, inventory[index]->sheet.price, pos);
}

void	draw_active_inventory(t_data *data, t_vector start)
{
	if (data->player.active_button && data->player.possession
		&& &data->player.possession->sheet.inventory_button
		== data->player.active_button
		&& data->player.active_button->active > 0)
	{
		if (data->player.active_button->active - 1 >= NON_EQUIP)
			start.y += data->button_scale_size / 2;
		start.x = start.x + (((data->player.active_button->active - 1) % 2)
				* data->button_scale_size);
		start.y = start.y + (((data->player.active_button->active - 1) / 2)
				* data->button_scale_size);
		draw_hover(data, start, 0xAA000000);
	}
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
	start.y = (data->win_size.y / 2) - (length / 2)
		- data->button_scale_size / 2;
	hover_index = inventory_hover_index(data);
	draw_equip(data, inventory, start, hover_index);
	draw_unequip(data, inventory, start, hover_index);
	draw_active_inventory(data, start);
	draw_invbutton_name(data, inventory, hover_index);
	show_other_inventory(data);
	draw_gold_button(data, start);
}
