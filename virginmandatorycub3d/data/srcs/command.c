#include "cub3d.h"

void	register_player_movement(t_data *data, int key, int pressed)
{
	if (key == 26)
		data->player.movement[0] = pressed;
	if (key == 4)
		data->player.movement[1] = pressed;
	if (key == 22)
		data->player.movement[2] = pressed;
	if (key == 7)
		data->player.movement[3] = pressed;
	if (key == 80)
		data->player.rotation[0] = pressed;
	if (key == 79)
		data->player.rotation[1] = pressed;
}

int	key_down_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 41)
		mlx_loop_end(data->mlx);
	if (key == 26 || key == 4 || key == 22 || key == 7
		|| key == 80 || key == 79)
		register_player_movement(data, key, 1);
	return (0);
}

int	key_up_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 26 || key == 4 || key == 22 || key == 7
		|| key == 80 || key == 79)
		register_player_movement(data, key, 0);
	return (0);
}

int	window_manager(int event, void *param)
{
	t_data	*data;

	data = param;
	if (event == 0)
		mlx_loop_end(data->mlx);
	return (0);
}
