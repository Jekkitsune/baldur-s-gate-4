/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vision_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:21:34 by fparis            #+#    #+#             */
/*   Updated: 2025/01/22 04:07:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_upper_wall_tex_column(t_data *data, t_texture *tex, t_impact *ray)
{
	if (ray->upper_wall_face % 2)
		return (fmod(data->player.pos.x * (data->scale * 2) \
		+ data->player.offset.x + data->scale
				+ (ray->direc.x * ray->upper_wall_length),
				(data->scale * 2)) * tex->size / (data->scale * 2));
	else
		return (fmod(data->player.pos.y * (data->scale * 2) \
		+ data->player.offset.y + data->scale
				+ (ray->direc.y * ray->upper_wall_length),
				(data->scale * 2)) * tex->size / (data->scale * 2));
}

void	draw_upper_wall_tex(t_data *data, int x, t_vector pos, t_impact *ray)
{
	int			tex_column;
	int			i;
	double		divided;
	t_texture	*tex;

	tex = ray->upper_wall_cell->upper_wall;
	divided = (double)tex->size / (double)(pos.y - pos.x);
	tex_column = get_upper_wall_tex_column(data, tex, ray);
	if ((ray->upper_wall_face == 1 || ray->upper_wall_face == 4))
		tex_column = tex->size - tex_column - 1;
	i = 0;
	i = ft_max(pos.x, i);
	while (i < pos.y && i < data->win_size.y)
	{
		if (i >= 0)
			data->screen_buffer[i][x]
				= tex->tab[tex_column][(int)((ft_abs(pos.x - i)) * divided)];
		i++;
	}
}

void	draw_upper_walls(t_data *data, float diff, t_impact *ray, int i)
{
	int			i2;
	int			size;
	t_vector	posy;

	if (!ray->upper_wall_cell || !ray->upper_wall_length)
		return ;
	size = (data->win_size.y / (ray->upper_wall_length / (data->scale * 2)));
	posy.x = (data->win_size.y - size) / 2 - size;
	posy.y = (data->win_size.y + size) / 2 - size;
	i2 = 0;
	while (i2 < diff)
	{
		draw_upper_wall_tex(data, i * diff + i2,
			vec(posy.x + data->player.pitch \
		+ (data->player.height / ray->upper_wall_length),
				posy.y + data->player.pitch
				+ (data->player.height / ray->upper_wall_length)), ray);
		i2++;
	}
}
