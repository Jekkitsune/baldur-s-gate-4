/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:21:42 by fparis            #+#    #+#             */
/*   Updated: 2024/08/28 20:26:06 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data)
{
	data->player.pos.x = 5;
	data->player.pos.y = 5;
	data->player.speed = 1;
	data->player.angle = 0;
	get_all_rays(data);
}
