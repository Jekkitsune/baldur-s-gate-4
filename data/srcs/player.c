/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:21:42 by fparis            #+#    #+#             */
/*   Updated: 2024/09/12 22:35:32 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data)
{
	data->player.speed = 1;
	data->player.camera_plane.x = cosf(angle_add(data->player.angle, M_PI / 2));
	data->player.camera_plane.y = sinf(angle_add(data->player.angle, M_PI / 2));
	data->player.direction.x = cosf(data->player.angle);
	data->player.direction.y = sinf(data->player.angle);
	get_all_rays(data);
}
