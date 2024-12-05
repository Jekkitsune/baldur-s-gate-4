/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:19:11 by fparis            #+#    #+#             */
/*   Updated: 2024/12/04 18:14:25 by fparis           ###   ########.fr       */
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
	int	i;

	ft_bzero(data, sizeof(t_data));
	data->test_key = 0;
	data->win_size.x = WIDTH;
	data->win_size.y = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_size.x, data->win_size.y, "Baldur's Gate 4");
	data->button_scale_size = 75 * data->win_size.x / 1920;
	data->scale = 10;
	data->render_distance = 500;
	data->sky_box = false;
	data->screen_buffer = ft_calloc(data->win_size.y, sizeof(uint32_t *));
	if (!data->screen_buffer)
		printf("malloc failed!\n");
	i = 0;
	while (i < data->win_size.y)
	{
		data->screen_buffer[i] = ft_calloc(data->win_size.x, sizeof(uint32_t));
		if (!data->screen_buffer[i])
			printf("malloc failed!\n");
		i++;
	}
	mlx_mouse_hide();
	mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2, data->win_size.y / 2);
	init_shape_tab(data);
	return (data);
}
