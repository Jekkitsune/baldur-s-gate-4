/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 06:14:08 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 07:12:54 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_equip(t_data *data, t_entity *inventory[INVENTORY_SIZE],
			t_vector start, int hover_index);
void	draw_unequip(t_data *data, t_entity *inventory[INVENTORY_SIZE],
			t_vector start, int hover_index);
void	draw_invbutton_name(t_data *data, t_entity *inventory[INVENTORY_SIZE],
			int index);
void	draw_active_inventory(t_data *data, t_vector start);
int		get_inv_index(int button_size, t_vector pos, t_vector mouse);
t_bool	add_to_inventory(t_data *data, t_entity *taker, t_entity *taken,
			t_bool no_equip);
void	shop(t_data *data, t_entity *caster, t_entity *target);

int	other_inventory_hover_index(t_data *data)
{
	t_vector	mouse;
	t_vector	pos;
	int			width;
	int			length;
	int			diff;

	if (!data->player.possession
		|| !data->player.possession->sheet.inventory_open)
		return (-1);
	diff = (data->button_scale_size * 2 + 10);
	width = data->button_scale_size * 2;
	length = (INVENTORY_SIZE / 2) * data->button_scale_size;
	pos.x = data->win_size.x - width - 10 - diff;
	pos.y = (data->win_size.y / 2) - (length / 2) - data->button_scale_size / 2;
	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (mouse.x >= pos.x && mouse.x < data->win_size.x - 10 - diff
		&& mouse.y >= pos.y && mouse.y < pos.y
		+ (data->button_scale_size * (NON_EQUIP / 2)))
		return (get_inv_index(data->button_scale_size, pos, mouse));
	pos.y += data->button_scale_size / 2;
	if (mouse.x >= pos.x && mouse.x < data->win_size.x - 10 - diff
		&& mouse.y >= pos.y + (data->button_scale_size * (NON_EQUIP / 2))
		&& mouse.y < pos.y + (data->button_scale_size * (INVENTORY_SIZE / 2)))
		return (get_inv_index(data->button_scale_size, pos, mouse));
	return (-1);
}

void	exchange_item(t_data *data, int item_index, t_entity *giver,
		t_entity *receiver)
{
	t_entity	*item;

	item = giver->sheet.inventory[item_index];
	if (!item)
		return ;
	if (add_to_inventory(data, receiver, item, true))
		giver->sheet.inventory[item_index] = NULL;
}

void	basic_loot(t_data *data, t_entity *caster, t_entity *target)
{
	int			index;

	index = inventory_hover_index(data);
	if (index >= NON_EQUIP && index < INVENTORY_SIZE)
	{
		exchange_item(data, index, caster, target);
		return ;
	}
	index = other_inventory_hover_index(data);
	if (index >= 0 && index < INVENTORY_SIZE)
	{
		exchange_item(data, index, target, caster);
		if (index < NON_EQUIP)
			refresh_stats(data, target);
		return ;
	}
}

void	check_click_other_inventory(t_data *data)
{
	t_button	*button;

	button = data->player.active_button;
	if (!data->shown_other_inventory || !button || !button->spellinfo.caster
		|| !button->spellinfo.target
		|| !button->spellinfo.caster->sheet.inventory_open)
		return ;
	if (!ft_strcmp(button->name, "Interact") && !data->player.shop_mode)
		basic_loot(data, button->spellinfo.caster, button->spellinfo.target);
	else if (!ft_strcmp(button->name, "Interact") && data->player.shop_mode)
		shop(data, button->spellinfo.caster, button->spellinfo.target);
}

void	draw_other_inventory(t_data *data, t_entity *inventory[INVENTORY_SIZE])
{
	int			width;
	int			length;
	int			hover_index;
	t_vector	pos;

	width = data->button_scale_size * 2;
	length = (INVENTORY_SIZE / 2) * data->button_scale_size;
	pos.x = data->win_size.x - width - 10 - (data->button_scale_size * 2 + 10);
	pos.y = (data->win_size.y / 2) - (length / 2)
		- data->button_scale_size / 2;
	hover_index = other_inventory_hover_index(data);
	draw_equip(data, inventory, pos, hover_index);
	draw_unequip(data, inventory, pos, hover_index);
	draw_invbutton_name(data, inventory, hover_index);
}
