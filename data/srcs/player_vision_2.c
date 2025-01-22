/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vision_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/22 02:24:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
