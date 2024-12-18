/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:48:52 by fparis            #+#    #+#             */
/*   Updated: 2024/12/16 23:33:23 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	update_button_action(t_data *data)
// {
// 	if (data->player.active_button && data->player.active_button->func)
// 		data->player.active_button->func(data, data->player.possession);
// }

void	use(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;
	t_vector	pos;

	data = data_param;
	entity = entity_param;
	if (!entity || !spell.summon || !spell.target)
		return ;
	if (!data->player.arrow)
		select_target(data);
	if (!check_dist_obstacle(data, entity, spell.range, spell.visible_target)
		|| !confirm(data->player.active_button) || !spell.summon)
		return ;
	pos = data->player.arrow->pos;
	spell.target = cycle_entity_cell(data, 0);
	remove_selector(data);
}

void	drop(t_data *data, t_entity *dropper, t_entity *dropped)
{
	t_list		*new_lst;
	int			i;

	if (!dropper || !dropped || !data->player.active_button)
		return ;
	i = data->player.active_button->active - 1;
	if (i < 0 || i >= INVENTORY_SIZE)
		return ;
	new_lst = ft_lstnew(dropped);
	if (!new_lst)
		return ;
	if (data->player.arrow)
	{
		dropped->offset = data->player.arrow->offset;
		dropped->pos = data->player.arrow->pos;
	}
	dropped->visible = true;
	ft_lstadd_front(&data->current_map->arr[dropped->pos.x][dropped->pos.y].entities, new_lst);
	if (dropped->active)
		add_active(data, dropped, dropped->behavior);
	dropper->sheet.inventory[i] = NULL;
}

void	throw(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;
	t_vector	pos;

	data = data_param;
	entity = entity_param;
	if (!data->player.arrow)
		select_target(data);
	if (!check_dist_obstacle(data, entity, spell.range, spell.visible_target)
		|| !confirm(data->player.active_button) || !spell.summon)
		return ;
	pos = data->player.arrow->pos;
	spell.target = cycle_entity_cell(data, 0);
	drop(data, entity, spell.summon);
	remove_selector(data);
	if (get_dist(pos, entity->pos) > 2)
	{
		damage(data, spell.summon, spell.nb);
		if (spell.target)
			damage(data, spell.target, spell.nb);
	}
}

void	set_inventory_button(t_data *data, t_entity *entity, int i)
{
	t_entity	*used;
	t_button	*button;

	if (i < 0 || i >= INVENTORY_SIZE)
		return ;
	used = entity->sheet.inventory[i];
	button = &entity->sheet.inventory_button;
	if (!used)
	{
		button->spellinfo.summon = NULL;
		button->func = use;
		remove_selector(data);
		return ;
	}
	button->spellinfo.caster = entity;
	button->spellinfo.range = ft_max(entity->sheet.stats[STR] / 2, 1);
	button->spellinfo.visible_target = true;
	button->spellinfo.summon = used;
	button->spellinfo.nb = used->sheet.weight / 3;
	if (used->sheet.type != consumable)
		button->func = throw;
	else
		button->func = use;
}

t_button	*button_inventory(t_data *data, t_entity *entity)
{
	static int	last = -1;
	int			current;
	t_button	*button;

	current = inventory_hover_index(data);
	if (current == -1)
	{
		last = -1;
		return (NULL);
	}
	button = &entity->sheet.inventory_button;
	if (last == -1)
	{
		last = current;
		button->active = current + 1;
		set_inventory_button(data, entity, current);
	}
	else if (last >= 0)
	{
		inventory_swap(entity, entity->sheet.inventory, last, current);
		last = -1;
	}
	return (button);
}

t_button	*current_button(t_data *data)
{
	int			i;
	t_button	*button;

	button = button_inventory(data, data->player.possession);
	if (button)
		return (button);
	i = get_hover_index(data);
	if (i >= 0 && i < NB_BUTTON)
		button = &data->player.possession->sheet.buttons[i];
	return (button);
}

void	check_button_click(t_data *data)
{
	t_button	*button;

	if (data->player.possession && data->player.possession->possess_control)
	{
		button = current_button(data);
		if (button)
		{
			if (button->func)
			{
				if (data->player.active_button)
					data->player.active_button->active = 0;
				if (data->player.active_button == button)
				{
					remove_selector(data);
					return ;
				}
				data->player.active_button = button;
				if (!button->active)
					button->active = 1;
				if (data->player.active_button && data->player.active_button->func)
					data->player.active_button->func(data, data->player.possession, data->player.active_button->spellinfo);
			}
		}
		else if (data->player.arrow && data->player.active_button && data->player.active_button->func)
			data->player.active_button->func(data, data->player.possession, data->player.active_button->spellinfo);
	}
}

void	draw_button_img(t_data *data, t_button button, t_vector start)
{
	t_vector	i;

	i.x = 1;
	while (i.x < data->button_scale_size)
	{
		i.y = 1;
		while (i.y < data->button_scale_size)
		{
			ft_pixel_put(data, i.y + start.y, i.x + start.x, button.img->tab[i.x][i.y]);
			i.y++;
		}
		i.x++;
	}
}

void	draw_borders(t_data *data, t_vector start)
{
	t_vector	i;

	ft_pixel_put(data, start.y, start.x, 0xFF4a3b28);
	i.x = 0;
	while (i.x++ < data->button_scale_size)
	{
		ft_pixel_put(data, start.y, start.x + i.x, 0xFF4a3b28);
		ft_pixel_put(data, start.y + i.x, start.x, 0xFF4a3b28);
		ft_pixel_put(data, start.y + data->button_scale_size, start.x + i.x, 0xFF4a3b28);
		ft_pixel_put(data, start.y + i.x, start.x + data->button_scale_size, 0xFF4a3b28);
	}
}

void	draw_button(t_data *data, t_button button, t_vector start)
{
	t_vector	i;

	draw_borders(data, start);
	i.x = 1;
	while (i.x < data->button_scale_size)
	{
		i.y = 1;
		while (i.y < data->button_scale_size)
		{
			ft_pixel_put(data, i.y + start.y, i.x + start.x, 0xDD6B5333);
			i.y++;
		}
		i.x++;
	}
	if (button.active)
		draw_hover(data, start, 0xAA000000);
	if (button.img)
		draw_button_img(data, button, start);
}

int	get_hover_index(t_data *data)
{
	t_vector	mouse_pos;
	int			res;
	int			margin;

	margin = (data->win_size.x - (data->button_scale_size * NB_BUTTON / 2)) / 2;
	res = -1;
	mlx_mouse_get_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x > margin && mouse_pos.x < data->win_size.x - margin
		&& mouse_pos.y > data->win_size.y - (data->button_scale_size * 2) - 10
			&& mouse_pos.y < data->win_size.y - 10)
	{
		res = mouse_pos.x - margin;
		res = (res / data->button_scale_size);
		if (mouse_pos.y > data->win_size.y - data->button_scale_size - 10)
			res += NB_BUTTON / 2;
	}
	return (res);
}

t_vector	get_hover_pos(t_data *data, int margin)
{
	t_vector	mouse_pos;
	t_vector	res;

	res.x = -1;
	res.y = -1;
	mlx_mouse_get_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x > margin && mouse_pos.x < data->win_size.x - margin
		&& mouse_pos.y > data->win_size.y - (data->button_scale_size * 2) - 10
			&& mouse_pos.y < data->win_size.y - 10)
	{
		res.x = mouse_pos.x - margin;
		res.x = (res.x / data->button_scale_size) * data->button_scale_size + margin;
		res.y = data->win_size.y - (data->button_scale_size * 2) - 10;
		if (mouse_pos.y > data->win_size.y - data->button_scale_size - 10)
			res.y += data->button_scale_size;
	}
	return (res);
}

void	draw_hover(t_data *data, t_vector start, uint32_t color)
{
	t_vector	i;

	if (start.x < 0)
		return ;
	i.x = 1;
	while (i.x < data->button_scale_size)
	{
		i.y = 1;
		while (i.y < data->button_scale_size)
		{
			ft_pixel_put(data, i.y + start.y, i.x + start.x, color);
			i.y++;
		}
		i.x++;
	}
}

void	draw_possession_button(t_data *data, t_button *buttons)
{
	int	i;
	int	margin;

	margin = (data->win_size.x - (data->button_scale_size * NB_BUTTON / 2)) / 2;
	if (margin > data->win_size.x || margin < 0)
		return ;
	i = 0;
	while (i < NB_BUTTON / 2)
	{
		draw_button(data, buttons[i], vec(margin + (i * data->button_scale_size), data->win_size.y - (data->button_scale_size * 2) - 10));
		i++;
	}
	i = 0;
	while (i < NB_BUTTON / 2)
	{
		draw_button(data, buttons[i + (NB_BUTTON / 2)], vec(margin + (i * data->button_scale_size), data->win_size.y - data->button_scale_size - 10));
		i++;
	}
	if (data->player.mouse_button[0])
		draw_hover(data, get_hover_pos(data, margin), 0x88000000);
	else
		draw_hover(data, get_hover_pos(data, margin), 0x44000000);
}
