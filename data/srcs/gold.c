/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gold.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:17:01 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 09:38:58 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		other_inventory_hover_index(t_data *data);
t_bool	add_to_inventory(t_data *data, t_entity *taker, t_entity *taken,
		t_bool no_equip);

void	show_price(t_data *data, int price, t_vector pos)
{
	t_strput	*to_put;
	char		*price_str;
	uint32_t	color;

	price_str = ft_itoa(price);
	if (!price_str)
		return ;
	if (price <= data->player.gold)
		color = 0xFFFFFFFF;
	else
		color = 0xFF9C1414;
	to_put = strput(ft_strjoin(price_str, " GOLD"), pos, 20, color);
	free(price_str);
	screen_string_put(data, to_put, 0);
}

void	add_gold(t_data *data, t_entity *to_add)
{
	if (to_add->sheet.type != gold)
		return ;
	data->player.gold  += to_add->sheet.price;
	destroy_entity(data, to_add);
}

void	draw_gold_button(t_data *data, t_vector inventory_start)
{
	t_entity	*gold;
	t_vector	mouse;
	t_vector	pos;

	pos.x = inventory_start.x + data->button_scale_size / 2;
	pos.y = inventory_start.y + data->button_scale_size * (INVENTORY_SIZE / 2)
		+ data->button_scale_size / 2;
	draw_borders(data, pos);
	draw_hover(data, pos, 0xDD6B5333);
	gold = get_prefab(data, "gold");
	if (gold && gold->sheet.portrait)
		show_tex(data, gold->sheet.portrait, pos);
	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (mouse.x >= pos.x && mouse.x <= pos.x + data->button_scale_size
		&& mouse.y >= pos.y && mouse.y <= pos.y + data->button_scale_size)
	{
		draw_hover(data, pos, 0x44000000);
		show_price(data, data->player.gold, vec(mouse.x, mouse.y - 5));
	}
}

void	buy_item(t_data *data, int item_index, t_entity *giver,
		t_entity *receiver)
{
	t_entity	*item;
	t_bool		selling;
	int			price;

	selling = in_party(data, giver);
	item = giver->sheet.inventory[item_index];
	if (!item)
		return ;
	price = item->sheet.price;
	if (!selling && price > data->player.gold)
		return ;
	if (add_to_inventory(data, receiver, item, true))
		giver->sheet.inventory[item_index] = NULL;
	if (selling)
		data->player.gold += price;
	else
		data->player.gold -= price;
}

void	shop(t_data *data, t_entity *caster, t_entity *target)
{
	int			index;

	index = inventory_hover_index(data);
	if (index >= NON_EQUIP && index < INVENTORY_SIZE)
	{
		buy_item(data, index, caster, target);
		return ;
	}
	index = other_inventory_hover_index(data);
	if (index >= NON_EQUIP && index < INVENTORY_SIZE)
	{
		buy_item(data, index, target, caster);
		return ;
	}
}
