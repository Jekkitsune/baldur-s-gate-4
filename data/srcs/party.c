/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:37:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/09 12:32:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_click_party_icon(t_data *data, t_vector mouse)
{
	t_vector	pos;
	t_list		*party;
	t_entity	*current;

	party = data->round_manager.party;
	if (!party)
		return ;
	pos.x = data->win_size.x / 2 + (data->button_scale_size * (NB_BUTTON / 4 + 1.5));
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
				possess(data, current);
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
	pos.x = data->win_size.x / 2 + (data->button_scale_size * (NB_BUTTON / 4 + 1.5));
	pos.y = data->win_size.y - (data->button_scale_size * 1.5) - 10;
	while (party)
	{
		if (mouse.x >= pos.x && mouse.x <= pos.x + data->button_scale_size
			&& mouse.y >= pos.y && mouse.y <= pos.y + data->button_scale_size)
			draw_hover(data, pos, 0x44000000);
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
	pos.x = data->win_size.x / 2 + (data->button_scale_size * (NB_BUTTON / 4 + 1.5));
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

void	follow_party_member(t_data *data, t_entity *follower, t_entity *to_follow)
{
	if (follower == data->player.possession || follower->behavior.path || !follower->active || !follower->sheet.alive)
		return ;
	if (get_dist(follower->pos, to_follow->pos) > 2)
	{
		follower->behavior.path = get_path(data, follower->pos, to_follow->pos, true);
		if (!follower->behavior.path)
		{
			printf("%s: \"can't follow\"\n", follower->sheet.name);
			return ;
		}
		follower->behavior.next = follower->behavior.func;
		follower->behavior.func = entity_moving_to;
	}
}

void	party_follow(t_data *data)
{
	t_list	*party;

	party = data->round_manager.party;
	while (party)
	{
		if (!party->next)
			follow_party_member(data, party->content, data->round_manager.party->content);
		else
			follow_party_member(data, party->content, party->next->content);
		party = party->next;
	}
}

void	free_round_manager(t_data *data)
{
	t_list	*lst;
	t_list	*to_free;

	lst = data->round_manager.party;
	while (lst)
	{
		to_free = lst;
		lst = lst->next;
		free(to_free);
	}
}
