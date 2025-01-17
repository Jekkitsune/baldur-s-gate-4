/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:19:30 by fparis            #+#    #+#             */
/*   Updated: 2025/01/17 00:29:55 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_action_box(t_data *data, int nb, t_vector pos, uint32_t color)
{
	draw_hover(data, pos, 0xDD8f6f45);
	draw_box_points(data, pos, ft_min(nb, 6), color);
}

void	show_health_nb(t_data *data, t_vector hp, t_vector pos, float scale)
{
	char		*str;
	char		*tmp1;
	char		*tmp2;
	t_strput	*to_put;

	tmp1 = ft_itoa(ft_max(hp.x, 0));
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
	empty_start = entity->sheet.hp * (end.x - pos->x) / entity->sheet.max_hp
		+ pos->x;
	if (empty_start < pos->x)
		empty_start = pos->x;
	draw_rectangle(data, vec(pos->x, start_y), vec(empty_start, end.y),
		0xFFD44242);
	if (empty_start < end.x)
		draw_rectangle(data, vec(empty_start, start_y), end, 0xAA702222);
	show_health_nb(data, vec(entity->sheet.hp, entity->sheet.max_hp),
		vec(pos->x, start_y + data->button_scale_size / 2),
		data->button_scale_size);
	pos->x = end.x;
}

void	draw_walk_left(t_data *data, t_entity *entity, t_vector pos)
{
	t_strput	*to_put;

	to_put = strput(ft_itoa(ft_max(entity->sheet.walked, 0)),
			vec(pos.x, (pos.y + data->button_scale_size) - 7),
			data->button_scale_size - 5, 0xFFFFFFFF);
	screen_string_put(data, to_put, 0);
}

void	draw_all_actions_box(t_data *data, t_entity *entity)
{
	t_vector	pos;
	int			i;

	pos.x = (data->win_size.x - (data->button_scale_size * NB_BUTTON / 2)) / 2;
	pos.y = data->win_size.y - (data->button_scale_size * 3) - 15;
	draw_possess_health(data, entity, &pos);
	pos.x += data->button_scale_size;
	draw_walk_left(data, entity, pos);
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
