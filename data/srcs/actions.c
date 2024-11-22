/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:45:04 by fparis            #+#    #+#             */
/*   Updated: 2024/11/21 13:31:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	*create_arrow(t_data *data)
{
	t_entity	*res;

	res = create_entity(data, data->player.pos, get_tex(data, "arrow"));
	possess_control(res, true);
	if (data->player.possession)
		teleport_entity(data, res, data->player.possession->pos, data->player.possession->offset);
	return (res);
}

void	remove_arrow(t_data *data)
{
	if (!data->player.arrow)
		return ;
	destroy_entity(data, data->player.arrow);
	if (data->player.active_button)
	{
		data->player.active_button->active = false;
		data->player.active_button = NULL;
	}
}

t_vector	select_target(t_data *data)
{
	t_vector	res;

	res.x = -1;
	res.y = -1;
	if (!data->player.arrow)
		data->player.arrow = create_arrow(data);
	return (res);
}

void	exemple_action(void *data_param, void *entity_param)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = entity_param;
	select_target(data);
}
