/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:48:52 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 08:58:21 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_button	*button_inventory(t_data *data, t_entity *entity);
void		check_click_other_inventory(t_data *data);
void		check_click_selection_screen(t_data *data);

t_button	*get_button_pointer(t_button *tab, char *name)
{
	int	i;

	i = 0;
	while (i < NB_BUTTON)
	{
		if (!ft_strcmp(tab[i].name, name))
			return (&tab[i]);
		i++;
	}
	return (NULL);
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

void	click_action_button(t_data *data, t_button *button)
{
	if (!button->func)
		return ;
	if (data->player.active_button)
	{
		reset_active_button(data);
		data->player.active_button->active = 0;
	}
	if (data->player.active_button == button)
	{
		remove_selector(data, false);
		return ;
	}
	data->player.active_button = button;
	if (!button->active)
		button->active = 1;
	if (data->player.active_button && data->player.active_button->func)
		data->player.active_button->func(data, data->player.possession,
			data->player.active_button->spellinfo);
}

void	check_action_button(t_data *data, t_vector mouse)
{
	t_button	*button;

	if (data->player.possession
		&& data->player.possession->possess_control
		&& data->player.possession->sheet.alive
		&& is_turn(data, data->player.possession))
	{
		button = current_button(data);
		if (button)
			click_action_button(data, button);
		else if (data->player.arrow && data->player.active_button
			&& data->player.active_button->func)
			data->player.active_button->func(data, data->player.possession,
				data->player.active_button->spellinfo);
		else
			check_click_end_turn(data, mouse);
	}
}

void	check_button_click(t_data *data)
{
	t_vector	mouse;

	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (!data->ready)
	{
		check_click_selection_screen(data);
		return ;
	}
	check_action_button(data, mouse);
	check_click_party_icon(data, mouse);
	check_click_participants_icon(data, mouse);
	check_click_other_inventory(data);
}
