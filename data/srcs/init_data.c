/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:19:11 by fparis            #+#    #+#             */
/*   Updated: 2024/09/18 18:41:05 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_shape_tab(t_data *data)
{
	data->check_shape[0] = default_shape;
	data->check_shape[1] = in_minimap;
}

t_data	*init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->test_key = 0;
	data->win_size.x = 1600;
	data->win_size.y = 900;
	data->scale = 10;
	data->render_distance = 500;
	data->test_length = 0;

	init_shape_tab(data);
	return (data);
}
