/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   participant_icon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:51:54 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 00:11:11 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	curr_poss(t_data *data, t_entity *current)
{
	if (!current)
		return (false);
	if (current == data->player.possession)
		unpossess(data);
	else
		possess(data, current);
	return (true);
}

void	check_click_participants_icon(t_data *data, t_vector mouse)
{
	t_vector	pos;
	t_list		*participants;
	int			i;

	i = 0;
	participants = data->round_manager.participants;
	if (!participants)
		return ;
	pos.x = 15;
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	while (participants)
	{
		if (mouse.x >= pos.x && mouse.x <= pos.x + data->button_scale_size
			&& mouse.y >= pos.y && mouse.y <= pos.y + data->button_scale_size
			&& i++ < MAX_PARTIC_ICON && curr_poss(data, participants->content))
			return ;
		participants = participants->next;
		pos.x += data->button_scale_size;
	}
}

void	check_participants_hover(t_data *data)
{
	t_vector	pos;
	t_list		*participants;
	t_vector	mouse;
	int			i;

	i = 0;
	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	participants = data->round_manager.participants;
	if (!participants)
		return ;
	pos.x = 15;
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	while (participants)
	{
		if (mouse.x >= pos.x && mouse.x <= pos.x + data->button_scale_size
			&& mouse.y >= pos.y && mouse.y <= pos.y + data->button_scale_size
			&& i++ < MAX_PARTIC_ICON)
			draw_hover(data, pos, 0x44000000);
		participants = participants->next;
		pos.x += data->button_scale_size;
	}
}

void	show_participants_icon(t_data *data)
{
	t_vector	pos;
	t_list		*participants;
	t_texture	*portrait;
	int			i;

	i = 0;
	participants = data->round_manager.participants;
	if (!participants)
		return ;
	pos.x = 15;
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	while (participants && i++ < MAX_PARTIC_ICON)
	{
		draw_borders(data, pos);
		portrait = ((t_entity *)(participants->content))->sheet.portrait;
		draw_hover(data, pos, 0xDD6B5333);
		if (portrait)
			draw_button_img(data, portrait, pos);
		pos.x += data->button_scale_size;
		participants = participants->next;
	}
	check_participants_hover(data);
}
