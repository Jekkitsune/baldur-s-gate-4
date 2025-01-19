#include "cub3d.h"

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
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_manager, data);
}

t_data	*init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->win_size.x = WIDTH;
	data->win_size.y = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_size.x,\
		data->win_size.y, "cub3d");
	data->scale = 10;
	data->screen_display = NULL;
	data->render_distance = 500;
	init_screen_buffer(data);
	mlx_mouse_hide();
	mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2,\
		data->win_size.y / 2);
	return (data);
}
