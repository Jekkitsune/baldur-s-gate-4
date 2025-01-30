/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:55:51 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 05:58:29 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_health_nb(t_data *data, t_vector hp, t_vector pos, float scale);

void	draw_rectangle(t_data *data, t_vector start, t_vector end,
	uint32_t color)
{
	int	i;
	int	i2;

	i = start.x;
	while (i < end.x)
	{
		i2 = start.y;
		while (i2 < end.y)
		{
			ft_pixel_put(data, i2, i, color);
			i2++;
		}
		i++;
	}
}

void	show_action_cost(t_data *data, t_spellinfo *info)
{
	t_vector	pos;
	int			i;
	t_entity	*entity;

	entity = data->player.possession;
	pos.x = (data->win_size.x - (data->button_scale_size
				* ((NB_BUTTON / 2) - 4 * 2))) / 2;
	pos.y = data->win_size.y - (data->button_scale_size * 3) - 15;
	if (info->cost_action || info->cost_attack)
		draw_hover(data, pos, 0xEEFFFFFF);
	pos.x += data->button_scale_size;
	if (info->cost_bonus)
		draw_hover(data, pos, 0xEEFFFFFF);
	i = 0;
	while (i < SPELL_MAX_LV)
	{
		pos.x += data->button_scale_size;
		if (info->cost_spell_slot == (i + 1) && entity->sheet.spell_slot[i])
			draw_hover(data, pos, 0xEEFFFFFF);
		i++;
	}
}

void	draw_health_name(t_data *data, t_entity *selected)
{
	t_strput	*to_put;

	if (selected->sheet.name)
	{
		draw_rectangle(data, vec((data->win_size.x / 2)
				- (ft_strlen(selected->sheet.name) * 6), 1),
			vec((data->win_size.x / 2) + (ft_strlen(selected->sheet.name)
					* (data->button_scale_size / 3)),
				data->button_scale_size - 2), 0xAA000000);
		to_put = strput(ft_strdup(selected->sheet.name), vec(data->win_size.x / \
		2, data->button_scale_size - 10), data->button_scale_size, 0xFFAAAAAA);
		to_put->centered = true;
		screen_string_put(data, to_put, 0);
	}
}

void	draw_health_bar(t_data *data, int empty_side, t_vector limit, int width)
{
	if (empty_side < limit.x)
		empty_side = limit.x;
	draw_rectangle(data, vec(limit.x, data->button_scale_size),
		vec(empty_side, data->button_scale_size + width), 0xFFD44242);
	if (empty_side < limit.y)
		draw_rectangle(data, vec(empty_side, data->button_scale_size),
			vec(limit.y, data->button_scale_size + width), 0xAA702222);
}

void	show_health_bar(t_data *data)
{
	t_entity	*selected;
	t_vector	limit;
	int			empty_side;
	int			size;
	int			width;

	selected = NULL;
	if (data->player.arrow)
		selected = cycle_entity_cell(data, 0);
	if (!selected)
		return ;
	draw_health_name(data, selected);
	if (selected->sheet.max_hp)
	{
		size = data->button_scale_size * 8;
		width = data->button_scale_size;
		limit.x = data->win_size.x / 2 - (size / 2);
		limit.y = data->win_size.x / 2 + (size / 2);
		empty_side = selected->sheet.hp * size / selected->sheet.max_hp
			+ limit.x;
		draw_health_bar(data, empty_side, limit, width);
		show_health_nb(data, vec(selected->sheet.hp, selected->sheet.max_hp),
			vec(limit.y + 5, data->button_scale_size * 2 - 5),
			data->button_scale_size);
	}
}
