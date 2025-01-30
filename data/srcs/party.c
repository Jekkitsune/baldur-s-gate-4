/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:37:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 12:37:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hover_character_button(t_data *data, t_vector pos, t_entity *entity,
		t_vector mouse_pos);

void	check_click_end_turn(t_data *data, t_vector mouse)
{
	t_vector	pos;

	if (!data->round_manager.combat)
		return ;
	pos.x = data->win_size.x / 2 - (data->button_scale_size
			* (1 + ((NB_BUTTON) / 4)));
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	if (mouse.x >= pos.x && mouse.x <= pos.x + data->button_scale_size
		&& mouse.y >= pos.y && mouse.y <= pos.y + data->button_scale_size)
		next_turn(data);
}

void	show_end_turn_button(t_data *data)
{
	t_vector	pos;
	t_vector	mouse;

	if (!data->round_manager.combat)
		return ;
	pos.x = data->win_size.x / 2 - (data->button_scale_size
			* (1 + ((NB_BUTTON) / 4)));
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	draw_borders(data, pos);
	draw_hover(data, pos, 0xDD6B5333);
	show_tex(data, get_tex(data, "end_turn"), pos);
	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (mouse.x >= pos.x && mouse.x <= pos.x + data->button_scale_size
		&& mouse.y >= pos.y && mouse.y <= pos.y + data->button_scale_size)
		draw_hover(data, pos, 0x44000000);
	
}

void	check_click_party_icon(t_data *data, t_vector mouse)
{
	t_vector	pos;
	t_list		*party;
	t_entity	*current;

	party = data->round_manager.party;
	if (!party)
		return ;
	pos.x = data->win_size.x / 2 + (data->button_scale_size
			* (NB_BUTTON / 4 + 1.5));
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	while (party)
	{
		if (mouse.x >= pos.x && mouse.x <= pos.x + data->button_scale_size
			&& mouse.y >= pos.y && mouse.y <= pos.y + data->button_scale_size)
		{
			current = party->content;
			if (current && current == data->player.possession)
				unpossess(data);
			else if (current)
				smooth_possess(data, current);
			return ;
		}
		party = party->next;
		pos.x += data->button_scale_size;
	}
}

void	check_party_hover(t_data *data)
{
	t_vector	pos;
	t_list		*party;
	t_vector	mouse;

	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	party = data->round_manager.party;
	if (!party)
		return ;
	pos.x = data->win_size.x / 2 + (data->button_scale_size
			* (NB_BUTTON / 4 + 1.5));
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	while (party)
	{
		if (mouse.x >= pos.x && mouse.x <= pos.x + data->button_scale_size
			&& mouse.y >= pos.y && mouse.y <= pos.y + data->button_scale_size)
			hover_character_button(data, pos, party->content, mouse);
		party = party->next;
		pos.x += data->button_scale_size;
	}
}

void	show_party_icon(t_data *data)
{
	t_vector	pos;
	t_list		*party;
	t_texture	*portrait;

	party = data->round_manager.party;
	if (!party)
		return ;
	pos.x = data->win_size.x / 2 + (data->button_scale_size
			* (NB_BUTTON / 4 + 1.5));
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	while (party)
	{
		draw_borders(data, pos);
		portrait = ((t_entity *)(party->content))->sheet.portrait;
		draw_hover(data, pos, 0xDD6B5333);
		if (portrait)
			draw_button_img(data, portrait, pos);
		pos.x += data->button_scale_size;
		party = party->next;
	}
	check_party_hover(data);
}
