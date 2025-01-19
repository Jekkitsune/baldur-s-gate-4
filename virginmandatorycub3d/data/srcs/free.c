#include "cub3d.h"

void	free_tex(t_texture *tex)
{
	int	i;

	i = 0;
	if (!tex)
		return ;
	if (tex->name)
		free(tex->name);
	if (tex->tab)
	{
		while (i < tex->size)
		{
			if (tex->tab[i])
				free(tex->tab[i]);
			i++;
		}
		free(tex->tab);
	}
	free(tex);
}

void	free_data(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = -1;
		while (++i < data->map->size.x)
				free(data->map->arr[i]);
		free(data->map->arr);
		free(data->map->path);
		free(data->map);
	}
	i = -1;
	while (++i < 4)
		free_tex(data->wall_tex[i]);
	if (data->screen_display)
		mlx_destroy_image(data->mlx, data->screen_display);
	i = -1;
	while (++i < data->win_size.y && data->screen_buffer\
		&& data->screen_buffer[i])
		free(data->screen_buffer[i]);
	if (data->screen_buffer)
		free(data->screen_buffer);
}

void	exit_free(t_data *data, char *error)
{
	free_data(data);
	ft_putstr_fd("Cub3d error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	exit(1);
}
