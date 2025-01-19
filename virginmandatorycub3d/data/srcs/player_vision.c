#include "cub3d.h"

int	get_tex_column(t_data *data, t_texture *tex, t_impact *ray)
{
	if (ray->face % 2)
		return (fmod(data->player.pos.x * (data->scale * 2) \
		+ data->player.offset.x + data->scale + (ray->direc.x * ray->length), \
		(data->scale * 2)) * tex->size / (data->scale * 2));
	else
		return (fmod(data->player.pos.y * (data->scale * 2) \
		+ data->player.offset.y + data->scale + (ray->direc.y * ray->length), \
		(data->scale * 2)) * tex->size / (data->scale * 2));
}

void	draw_wall(t_data *data, int x, t_vector pos, t_impact *ray)
{
	int			tex_column;
	int			i;
	double		divided;
	t_texture	*tex;

	tex = ray->cell->tex[ray->face - 1];
	divided = (double)tex->size / (double)(pos.y - pos.x);
	tex_column = get_tex_column(data, tex, ray);
	if ((ray->face == 1 || ray->face == 4))
		tex_column = tex->size - tex_column - 1;
	i = -1;
	while (++i < pos.x)
		data->screen_buffer[i][x] = data->cc;
	while (i < pos.y && i < data->win_size.y)
	{
		if (i >= 0)
			data->screen_buffer[i][x]
				= tex->tab[tex_column][(int)((ft_abs(pos.x - i)) * divided)];
		i++;
	}
	while (++i < data->win_size.y)
		data->screen_buffer[i][x] = data->fc;
}

void	draw_ray(t_data *data, float diff, t_impact *ray, int i)
{
	int			i2;
	int			size;
	t_vector	posy;

	if (ray->face == 0)
		return ;
	if (ray->length <= 0)
		size = 0;
	else
		size = (data->win_size.y / (ray->length / (data->scale * 2)));
	posy.x = (data->win_size.y - size) / 2;
	posy.y = (data->win_size.y + size) / 2;
	i2 = 0;
	while (i2 < diff)
	{
		draw_wall(data, i * diff + i2, vec(posy.x + data->player.pitch \
		+ (data->player.height / ray->length), posy.y + data->player.pitch \
		+ (data->player.height / ray->length)), ray);
		i2++;
	}
}

void	show_screen(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < NB_RAYS)
		draw_ray(data, (float)data->win_size.x / (float)NB_RAYS,\
		&data->player.vision[i], i);
	if (!data->screen_display)
		data->screen_display = mlx_new_image(data->mlx, data->win_size.x,\
		data->win_size.y);
	i = -1;
	while (++i < data->win_size.y)
	{
		j = -1;
		while (++j < data->win_size.x)
			mlx_set_image_pixel(data->mlx, data->screen_display, j, i,
				data->screen_buffer[i][j]);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->screen_display, 0, 0);
}

void	get_all_rays(t_data *data)
{
	double		camera;
	int			i;
	t_vectorf	direc;

	i = 0;
	while (i < NB_RAYS)
	{
		camera = (2 * i / (double) NB_RAYS) - 1;
		direc.x = data->player.direction.x + data->player.camera_plane.x
			* camera;
		direc.y = data->player.direction.y + data->player.camera_plane.y
			* camera;
		data->player.vision[i] = get_impact(data->player.pos, direc, data);
		i++;
	}
}
