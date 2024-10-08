/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:19:11 by fparis            #+#    #+#             */
/*   Updated: 2024/09/19 18:35:18 by fparis           ###   ########.fr       */
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
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_size.x, data->win_size.y, "Baldur's Gate 4");
	data->scale = 10;
	data->render_distance = 500;
	data->test_length = 0;
	mlx_mouse_hide();
	init_shape_tab(data);
	return (data);
}
