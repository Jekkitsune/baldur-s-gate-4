/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_possess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 01:18:56 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 01:08:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	possess_control(t_entity *entity, t_bool value)
{
	if (!entity)
		return ;
	entity->possess_control = value;
}

void	possess(t_data *data, t_entity *entity)
{
	if (!entity || !in_bound(data->current_map, entity->pos))
		return ;
	mlx_mouse_show();
	data->player.focus_mode = 1;
	data->player.focus_dist = 40;
	data->player.possession = entity;
	data->player.pos = data->player.possession->pos;
	data->player.offset = data->player.possession->offset;
	data->player.height = 0;
	data->player.pitch = 0;
}

void	unpossess(t_data *data)
{
	mlx_mouse_hide();
	data->player.focus_mode = 0;
	data->player.height = 0;
	data->player.pitch = 0;
	data->player.pos = data->player.possession->pos;
	data->player.offset = data->player.possession->offset;
	data->player.possession = NULL;
	data->player.active_button = NULL;
}
