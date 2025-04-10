/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:13:43 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 14:15:17 by fparis           ###   ########.fr       */
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

void	init_properties_tab(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = open("data/properties", O_RDONLY);
	if (fd == -1)
		exit_free(data, "No properties file");
	data->properties_tab[i] = get_next_line(fd);
	while (i < NB_PROPERTIES - 1 && data->properties_tab[i])
	{
		i++;
		data->properties_tab[i] = get_next_line(fd);
		data->properties_tab[i][ft_strlen(data->properties_tab[i]) - 1] = 0;
	}
	finish_gnl(fd);
	close(fd);
}

t_data	*init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->win_size.x = WIDTH;
	data->win_size.y = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_size.x, data->win_size.y,
			"Baldur's Gate 4");
	if (!data->mlx || !data->win)
		exit_free(data, "Error while loading mlx");
	data->button_scale_size = 75 * data->win_size.x / 1920;
	data->scale = 10;
	data->render_distance = 5000;
	init_screen_buffer(data);
	init_shape_tab(data);
	mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2,
		data->win_size.y / 2);
	srand(time(NULL));
	mlx_set_fps_goal(data->mlx, FPS_CAP);
	data->round_manager.party_lvl = 1;
	init_properties_tab(data);
	return (data);
}
