/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:55:51 by fparis            #+#    #+#             */
/*   Updated: 2025/01/08 17:37:58 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(t_data *data, t_vector start, t_vector end, uint32_t color)
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

void	draw_action_box(t_data *data, int nb, t_vector pos, uint32_t color)
{
	t_strput	*to_put;

	draw_hover(data, pos, 0xDD8f6f45);
	draw_box_points(data, pos, ft_min(nb, 6), color);
}

void	show_health_nb(t_data *data, t_vector hp, t_vector pos, float scale)
{
	char		*str;
	char		*tmp1;
	char		*tmp2;
	t_strput	*to_put;

	tmp1 = ft_itoa(hp.x);	
	tmp2 = ft_itoa(hp.y);
	str = ft_vajoin(tmp1, " / ", tmp2, NULL);
	free(tmp1);
	free(tmp2);
	to_put = strput(str, pos, scale, 0xFF000000);
	screen_string_put(data, to_put, 0);
}

void	draw_possess_health(t_data *data, t_entity *entity, t_vector *pos)
{
	t_vector	end;
	int			empty_start;
	int			start_y;

	if (!entity->sheet.max_hp)
		return ;
	end.x = pos->x + data->button_scale_size * 2;
	end.y = pos->y + data->button_scale_size - (data->button_scale_size / 4);
	start_y = pos->y + (data->button_scale_size / 4);
	empty_start = entity->sheet.hp * (end.x - pos->x) / entity->sheet.max_hp + pos->x;
	if (empty_start < pos->x)
		empty_start = pos->x;
	draw_rectangle(data, vec(pos->x, start_y), vec(empty_start, end.y), 0xFFD44242);
	if (empty_start < end.x)
		draw_rectangle(data, vec(empty_start, start_y), end, 0xAA702222);
	show_health_nb(data, vec(entity->sheet.hp, entity->sheet.max_hp), vec(pos->x, start_y + data->button_scale_size / 2), data->button_scale_size);
	pos->x = end.x;
}

void	draw_all_actions_box(t_data *data, t_entity *entity)
{
	t_vector	pos;
	t_strput	*to_put;
	int			i;

	pos.x = (data->win_size.x - (data->button_scale_size * NB_BUTTON / 2)) / 2;
	pos.y = data->win_size.y - (data->button_scale_size * 3) - 15;
	draw_possess_health(data, entity, &pos);
	pos.x += data->button_scale_size;
	to_put = strput(ft_itoa(ft_max(entity->sheet.walked, 0)), vec(pos.x, (pos.y + data->button_scale_size) - 7), data->button_scale_size - 5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 0);
	pos.x += data->button_scale_size;
	if (entity->sheet.attack_left > 0)
		draw_action_box(data, entity->sheet.attack_left, pos, 0xFFDB2121);
	else
		draw_action_box(data, entity->sheet.action, pos, 0xFF17BF11);
	pos.x += data->button_scale_size;
	draw_action_box(data, entity->sheet.bonus_action, pos, 0xFFE69010);
	i = 0;
	while (i < SPELL_MAX_LV)
	{
		pos.x += data->button_scale_size;
		if (entity->sheet.spell_slot[i])
			draw_action_box(data, entity->sheet.spell_slot[i], pos, 0xFF109FE6);
		i++;
	}
}

void	show_action_cost(t_data *data, t_spellinfo *info)
{
	t_vector	pos;
	int			i;
	t_entity	*entity;

	entity = data->player.possession;
	pos.x = (data->win_size.x - (data->button_scale_size * ((NB_BUTTON / 2) - 4 * 2))) / 2;
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
	if (selected->sheet.name)
	{
		draw_rectangle(data, vec((data->win_size.x / 2) - (ft_strlen(selected->sheet.name) * 6), 1),
			vec((data->win_size.x / 2) + (ft_strlen(selected->sheet.name) * (data->button_scale_size / 3)), data->button_scale_size - 2), 0xAA000000);
		screen_string_put(data, strput(ft_strdup(selected->sheet.name), vec((data->win_size.x / 2)
			- (ft_strlen(selected->sheet.name) * 5),
				data->button_scale_size - 10), data->button_scale_size, 0xFFAAAAAA), 0);
	}
	if (selected->sheet.max_hp)
	{
		size = data->button_scale_size * 8;
		width = data->button_scale_size;
		limit.x = data->win_size.x / 2 - (size / 2);
		limit.y = data->win_size.x / 2 + (size / 2);
		empty_side = selected->sheet.hp * size / selected->sheet.max_hp + limit.x;
		if (empty_side < limit.x)
			empty_side = limit.x;
		draw_rectangle(data, vec(limit.x, data->button_scale_size), vec(empty_side, data->button_scale_size + width), 0xFFD44242);
		if (empty_side < limit.y)
			draw_rectangle(data, vec(empty_side, data->button_scale_size), vec(limit.y, data->button_scale_size + width), 0xAA702222);
		show_health_nb(data, vec(selected->sheet.hp, selected->sheet.max_hp), vec(limit.y + 5, data->button_scale_size * 2 - 5), data->button_scale_size);
	}
}
