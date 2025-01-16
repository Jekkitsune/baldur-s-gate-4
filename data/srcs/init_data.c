/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:13:43 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 16:14:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_shape_tab(t_data *data)
{
	data->check_shape[0] = default_shape;
	data->check_shape[1] = in_minimap;
}

void	init_screen_buffer(t_data *data)
{
	int	i;

	data->screen_buffer = ft_calloc(data->win_size.y, sizeof(uint32_t *));
	if (!data->screen_buffer)
		exit_free(data, "Could not load screen buffer");
	i = 0;
	while (i < data->win_size.y)
	{
		data->screen_buffer[i] = ft_calloc(data->win_size.x, sizeof(uint32_t));
		if (!data->screen_buffer[i])
			exit_free(data, "Could not load screen buffer");
		i++;
	}
}

void	init_mlx_events(t_data *data)
{
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_down_manager, data);
	mlx_on_event(data->mlx, data->win, MLX_KEYUP, key_up_manager, data);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEWHEEL, mouse_wheel_manager,
		data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_manager, data);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEDOWN, mouse_down_manager, data);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEUP, mouse_up_manager, data);
}

t_data	*init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->test_key = 0;
	data->win_size.x = WIDTH;
	data->win_size.y = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_size.x, data->win_size.y,
			"Baldur's Gate 4");
	data->button_scale_size = 75 * data->win_size.x / 1920;
	data->scale = 10;
	data->render_distance = 500;
	data->sky_box = false;
	init_screen_buffer(data);
	mlx_mouse_hide();
	mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2,
		data->win_size.y / 2);
	init_shape_tab(data);
	srand(time(NULL));
	return (data);
}
