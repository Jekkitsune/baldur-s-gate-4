/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_screen_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 08:30:17 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/31 13:42:11 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_click_start(t_data *data, t_vector pos, t_vector size)
{
	t_vector	mouse;

	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (mouse.x >= pos.x && mouse.x <= pos.x + size.x
		&& mouse.y >= pos.y && mouse.y <= pos.y + size.y
		&& ft_lstsize(data->round_manager.party) == 4)
	{
		data->ready = true;
		if (data->round_manager.party)
			possess(data, data->round_manager.party->content);
	}
}

t_bool	check_click_character(t_data *data, t_vector pos, char *class, int size)
{
	t_vector	mouse;
	t_entity	*entity;

	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (mouse.x >= pos.x && mouse.x <= pos.x + size
		&& mouse.y >= pos.y && mouse.y <= pos.y + size)
	{
		entity = in_party_name(data, class);
		if (entity)
			destroy_entity(data, entity);
		else if (ft_lstsize(data->round_manager.party) < 4)
		{
			entity = spawn_entity(data, get_prefab(data, class),
					data->player.pos, ft_strdup(class));
			join_party(data, entity);
		}
		return (true);
	}
	return (false);
}

void	check_click_selection_screen(t_data *data)
{
	int	size;

	size = data->win_size.y * 0.35;
	if (check_click_character(data, vec(data->win_size.x * 0.1,
				data->win_size.y * 0.1), "barbarian", size))
		return ;
	if (check_click_character(data, vec(data->win_size.x * 0.4,
				data->win_size.y * 0.55), "rogue", size))
		return ;
	if (check_click_character(data, vec(data->win_size.x * 0.4,
				data->win_size.y * 0.1), "warlock", size))
		return ;
	if (check_click_character(data, vec(data->win_size.x * 0.1,
				data->win_size.y * 0.55), "wizard", size))
		return ;
	if (check_click_character(data, vec(data->win_size.x * 0.7,
				data->win_size.y * 0.1), "monk", size))
		return ;
	if (check_click_character(data, vec(data->win_size.x * 0.7,
				data->win_size.y * 0.55), "ranger", size))
		return ;
	check_click_start(data, vec(data->win_size.x * 0.92,
			data->win_size.y * 0.03),
		vec(data->win_size.x * 0.06, data->win_size.y * 0.06));
}
