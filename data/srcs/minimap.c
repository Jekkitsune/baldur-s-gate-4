/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:33:33 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 12:32:14 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_chunk_tab(t_minimap *minimap);

void	draw_figs_loop(t_data *data, t_vector offset, t_vector pos, int color)
{
	t_vector	i;

	i.y = -1;
	while (++i.y < data->minimap.fig_size)
	{
		i.x = -1;
		while (++i.x < data->minimap.fig_size)
		{
			if ((pos.x + i.x + offset.x >= 0)
				&& (pos.x + i.x + offset.x < data->minimap.ui_size)
				&& (pos.y + i.y + offset.y >= 0)
				&& (pos.y + i.y + offset.y < data->minimap.ui_size))
			{
				if (i.x == 0 || i.x == data->minimap.fig_size - 1 || i.y == 0
					|| i.y == data->minimap.fig_size - 1)
					ft_pixel_put(data, pos.y + i.y + offset.y
						+ data->minimap.pos.y, pos.x + i.x + offset.x
						+ data->minimap.pos.x, 0xFFDEDEE0);
				else
					ft_pixel_put(data, pos.y + i.y + offset.y
						+ data->minimap.pos.y, pos.x + i.x + offset.x
						+ data->minimap.pos.x, color);
			}
		}
	}
}

void	draw_figs(t_data *data, t_vector fig)
{
	int			color;
	t_vector	offset;
	t_vector	pos;

	pos.x = fig.x * data->minimap.fig_size;
	pos.y = fig.y * data->minimap.fig_size;
	offset.x = -((data->minimap.chunk_size * data->minimap.fig_size) / 2)
		+ (data->minimap.ui_size / 2)
		- (data->player.offset.x * (data->minimap.fig_size / data->scale) / 2);
	offset.y = -((data->minimap.chunk_size * data->minimap.fig_size) / 2)
		+ (data->minimap.ui_size / 2)
		- (data->player.offset.y * (data->minimap.fig_size / data->scale) / 2);
	if (data->minimap.chunk[fig.x][fig.y] == WALL)
		color = 0xFF5D5D5E;
	else
		color = 0xFFA7CC83;
	draw_figs_loop(data, offset, pos, color);
}

void	draw_player_vision(t_data *data)
{
	t_vector	center_map;
	t_vector	p_delta_posx;
	int			i;

	center_map = vec(data->minimap.ui_size / 2 \
	+ data->minimap.pos.x, data->minimap.ui_size / 2 + data->minimap.pos.y);
	draw_square(data, center_map, linfo(0xFFb734eb, 4, data->check_shape[0]));
	i = 0;
	while (i < NB_RAYS)
	{
		p_delta_posx.x = (data->player.vision[i].direc.x \
		* data->player.vision[i].length) * (data->minimap.fig_size \
		/ (data->scale)) / 2 + center_map.x;
		p_delta_posx.y = (data->player.vision[i].direc.y \
		* data->player.vision[i].length) * (data->minimap.fig_size \
		/ (data->scale)) / 2 + center_map.y;
		draw_line(data, center_map, p_delta_posx,
			linfo(0xFF00FF00, 1, data->check_shape[1]));
		i += 7;
	}
}

void	show_minimap(t_data *data)
{
	t_vector	i;

	i.y = 0;
	while (i.y < data->minimap.chunk_size)
	{
		i.x = 0;
		while (i.x < data->minimap.chunk_size)
		{
			draw_figs(data, i);
			i.x++;
		}
		i.y++;
	}
	draw_player_vision(data);
}

int	create_minimap(t_data *data, int ui_size, int fig_size)
{
	data->minimap.ui_size = ui_size;
	data->minimap.fig_size = fig_size;
	data->minimap.pos.x = 10;
	data->minimap.pos.y = 10;
	data->minimap.chunk_size = 0;
	data->minimap.chunk = NULL;
	if (!create_chunk_tab(&data->minimap))
		return (0);
	return (1);
}
