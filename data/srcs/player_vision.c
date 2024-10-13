/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2024/10/13 04:44:00 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_data *data, int x, t_vector pos, t_impact *ray)
{
	int 		tex_column;
	int			i;
	double		divided;
	t_texture	*tex;

	tex = ray->cell->tex[ray->face - 1];
	divided = (double)tex->size / (double)(pos.y - pos.x);
	if (ray->face % 2)
		tex_column = fmod(data->player.pos.x * (data->scale * 2) + data->player.offset.x + data->scale + (ray->direc.x * ray->length), (data->scale * 2)) * tex->size / (data->scale * 2);
	else
		tex_column = fmod(data->player.pos.y * (data->scale * 2) + data->player.offset.y + data->scale + (ray->direc.y * ray->length), (data->scale * 2)) * tex->size / (data->scale * 2);
	if ((ray->face == 1 || ray->face == 4))
		tex_column = tex->size - tex_column - 1;
	i = pos.x;
	// while (i < pos.x && i < data->win_size.y)
	// {
	// 	mlx_set_image_pixel(data->mlx, data->screen_display, x, i, 0xFF0000BB);
	// 	i++;
	// }
	while (i < pos.y && i < data->win_size.y)
	{
		mlx_set_image_pixel(data->mlx, data->screen_display, x, i, tex->tab[tex_column][(int)((ft_abs(pos.x - i)) * divided)]);
		i++;
	}
	// while (i < data->win_size.y)
	// {
	// 	mlx_set_image_pixel(data->mlx, data->screen_display, x, i, 0xFF00BB00);
	// 	i++;
	// }
}

void	get_all_rays_old(t_data *data)
{
	int			i;
	float		rad_i;
	t_vectorf	direc;
	float		space;

	i = 0;
	space = (float)FOV / NB_RAYS;
	rad_i = data->player.angle - (space * (NB_RAYS / 2));
	if (rad_i < 0)
		rad_i += 2 * M_PI;
	while (i < NB_RAYS)
	{
		direc.x = cosf(rad_i);
		direc.y = sinf(rad_i);
		data->player.vision[i] = get_impact(data->player.pos, direc, data);
		data->player.vision[i].angle = rad_i;
		rad_i += space;
		if (rad_i > 2 * M_PI)
			rad_i -= 2 * M_PI;
		i++;
	}
}

void	get_all_rays(t_data *data)
{
	double		camera;
	int			i;
	//float		diff;
	t_vectorf	direc;

	i = 0;
	while (i < NB_RAYS)
	{
		camera = (2 * i / (double) NB_RAYS) - 1;
		direc.x = data->player.direction.x + data->player.camera_plane.x * camera;
		direc.y = data->player.direction.y + data->player.camera_plane.y * camera;
		data->player.vision[i] = get_impact(data->player.pos, direc, data);
		i++;
	}
}

float	fix_fisheye(t_data *data, t_impact ray, float size)
{
	float	p_angle;
	float	r_angle;
	float	c_angle;

	p_angle = data->player.angle;
	r_angle = ray.angle;
	c_angle = p_angle - r_angle;
	if (c_angle > 2 * M_PI)
		c_angle -= 2 * M_PI;
	if (c_angle < 0)
		c_angle += 2 * M_PI;
	size *= cosf(c_angle);
	return (size);
}

void	draw_ray(t_data *data, float diff, t_impact ray, int i)
{
	int			i2;
	int			size;
	int			color;
	t_vector	posy;

	if (ray.face == 0)
		return ;
	if (ray.length <= 0)
		size = 0;
	else
		size = (data->win_size.y / (ray.length / (data->scale * 2)));
	if (ray.face == 1 || ray.face == 3)
		color = 0xFF349CEB;
	else
		color = 0xFF3172A3;
	posy.x = (data->win_size.y - size) / 2;
	posy.y = (data->win_size.y + size) / 2;
	i2 = 0;
	while (i2 < diff)
	{	
		draw_wall(data, i * diff + i2, vec(posy.x + data->player.pitch + (data->player.height / ray.length), posy.y + data->player.pitch + (data->player.height / ray.length)), &ray);
		//draw_line_raycast(data, i * diff + i2, posy.x + data->player.pitch + (data->player.height / ray.length), posy.y + data->player.pitch + (data->player.height / ray.length), color, &ray);
		i2++;
	}
}

void	show_floor(t_data *data)
{
	int			x;
	int			y;
	t_vectorf	ray_dir_0;
	t_vectorf	ray_dir_1;
	int			p;
	float		pos_z;
	float		row_distance;
	t_vectorf	floor_step;
	t_vectorf	floor;
	t_vector	cell;
	t_vector	t;
	uint32_t	color;
	t_vector	t_skybox;

	y = 0;
	while (y < data->win_size.y)
	{
		ray_dir_0.x = data->player.direction.x - data->player.camera_plane.x;
		ray_dir_0.y = data->player.direction.y - data->player.camera_plane.y;
		ray_dir_1.x = data->player.direction.x + data->player.camera_plane.x;
		ray_dir_1.y = data->player.direction.y + data->player.camera_plane.y;
		
		p = y - data->win_size.y / 2;
		pos_z = 0.5 * data->win_size.y;
		row_distance = pos_z / p;

		floor_step.x = row_distance * (ray_dir_1.x - ray_dir_0.x) / data->win_size.x;
		floor_step.y = row_distance * (ray_dir_1.y - ray_dir_0.y) / data->win_size.x;
		
		floor.x = (data->player.pos.x + (5 + data->player.offset.x / 2) / 10) + row_distance * ray_dir_0.x;
		floor.y = (data->player.pos.y + (5 + data->player.offset.y / 2) / 10) + row_distance * ray_dir_0.y;

		x = 0;
		while (++x < data->win_size.x)
		{
			cell.x = (int) floor.x;
			cell.y = (int) floor.y;

			t.x = ((int) (data->textures[0]->size * (floor.x - cell.x)) % (data->textures[0]->size - 1));
			t.y = ((int) (data->textures[0]->size * (floor.y - cell.y)) % (data->textures[0]->size - 1));
			if (t.x < 0)
				t.x = 0;
			if (t.y < 0)
				t.y = 0;

			floor.x += floor_step.x;
			floor.y += floor_step.y;

			color = data->textures[0]->tab[t.x][t.y];
			mlx_set_image_pixel(data->mlx, data->screen_display, x, y, color);
			//data->screen_buffer[y][x] = color;

			//t_skybox.x = (data->textures[0]->size - 1) * (((cell.x * 100) / data->current_map->size.x) / 100);
			//printf("%d %d %d\n", cell.x, data->current_map->size.x, (((cell.x * 100) / data->current_map->size.x) / 100));
			//printf("%d\n", t_skybox.x);
			//t_skybox.y = (data->textures[0]->size - 1) * (((cell.y * 100) / data->current_map->size.y) / 100);
			//printf("%i, %i %i\n", data->textures[0]->size, t_skybox.x, t_skybox.y);

			color = data->textures[1]->tab[t.x][t.y];
			mlx_set_image_pixel(data->mlx, data->screen_display, x, data->win_size.y - y - 1, color);
			//data->screen_buffer[data->win_size.y - y - 1][x] = color;
		}

		y++;
	}
}

void	show_screen(t_data *data)
{
	int			i;
	float		diff;
	int			color;
	t_impact	*vision;

	if (!data->screen_display)
		data->screen_display = mlx_new_image(data->mlx, data->win_size.x, data->win_size.y);
	show_floor(data);
	vision = data->player.vision;
	i = 0;
	diff = (float)data->win_size.x / (float)NB_RAYS;
	while (i < NB_RAYS)
	{
		draw_ray(data, diff, data->player.vision[i], i);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->screen_display, 0, 0);
}
