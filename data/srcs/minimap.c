/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 21:33:33 by fparis            #+#    #+#             */
/*   Updated: 2024/12/19 22:21:47 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_chunk_tab(t_minimap *minimap)
{
	int	i;	

	minimap->chunk_size = (minimap->UI_size / minimap->fig_size) + 2;
	minimap->chunk_size += (minimap->chunk_size % 2 == 0);
	i = 0;
	minimap->chunk = ft_calloc(sizeof(char *), minimap->chunk_size);
	if (!minimap->chunk)
		return (0);
	while (i < minimap->chunk_size)
	{
		minimap->chunk[i] = ft_calloc(sizeof(char *), minimap->chunk_size);
		if (!minimap->chunk[i])
		{
			ft_free_tab(minimap->chunk);
			return (0);
		}
		i++;
	}
	return (1);
}	

void	update_chunk(t_data *data)
{
	t_vector	i_chunk;
	t_vector	i_map;
	
	i_map.x = data->player.pos.x - (data->minimap.chunk_size / 2);
	i_map.y = data->player.pos.y - (data->minimap.chunk_size / 2);
	i_chunk.y = 0;
	while (i_chunk.y < data->minimap.chunk_size)
	{
		i_chunk.x = 0;
		while (i_chunk.x < data->minimap.chunk_size)
		{
			if (in_bound(data->current_map, vec_sum(i_map, i_chunk)))
				data->minimap.chunk[i_chunk.x][i_chunk.y] = data->current_map->arr[i_map.x + i_chunk.x][i_map.y + i_chunk.y].type;
			else
				data->minimap.chunk[i_chunk.x][i_chunk.y] = 0;
			i_chunk.x++;
		}
		i_chunk.y++;
	}
}

void	draw_figs(t_data *data, t_vector fig)
{
	t_vector	i;
	int			color;
	t_vector	offset;
	t_vector	pos;

	pos.x = fig.x * data->minimap.fig_size;
	pos.y = fig.y * data->minimap.fig_size;
	offset.x = -((data->minimap.chunk_size * data->minimap.fig_size) / 2) + (data->minimap.UI_size / 2)
		- (data->player.offset.x * (data->minimap.fig_size / data->scale) / 2);
	offset.y = -((data->minimap.chunk_size * data->minimap.fig_size) / 2) + (data->minimap.UI_size / 2)
		- (data->player.offset.y * (data->minimap.fig_size / data->scale) / 2);
	if (data->minimap.chunk[fig.x][fig.y] == WALL)
		color = 0xFF5D5D5E;
	else
		color = 0xFFA7CC83;
	i.y = 0;
	while (i.y < data->minimap.fig_size)
	{
		i.x = 0;
		while (i.x < data->minimap.fig_size)
		{
			if ((pos.x + i.x + offset.x >= 0) && (pos.x + i.x + offset.x < data->minimap.UI_size)
				&& (pos.y + i.y + offset.y >= 0) && (pos.y + i.y + offset.y < data->minimap.UI_size))
			{
				if (i.x == 0 || i.x == data->minimap.fig_size - 1 || i.y == 0 || i.y == data->minimap.fig_size - 1)
					//mlx_set_image_pixel(data->mlx, pos.x + i.x + offset.x, pos.y + i.y + offset.y, 0xFFDEDEE0);
					ft_pixel_put(data, pos.y + i.y + offset.y + data->minimap.pos.y, pos.x + i.x + offset.x + data->minimap.pos.x, 0xFFDEDEE0);
				else
					//mlx_set_image_pixel(data->mlx, pos.x + i.x + offset.x, pos.y + i.y + offset.y, color);
					ft_pixel_put(data, pos.y + i.y + offset.y + data->minimap.pos.y, pos.x + i.x + offset.x + data->minimap.pos.x, color);
			}
			i.x++;
		}
		i.y++;
	}
}

void	print_chunk(t_data *data)
{
	int	i;
	int	i2;

	i = 0;
	while (i < data->minimap.chunk_size)
	{
		i2 = 0;
		while (i2 < data->minimap.chunk_size)
		{
			if (data->minimap.chunk[i2][i])
				printf("%c", data->minimap.chunk[i2][i]);
			else
				printf("o");
			i2++;
		}
		printf("\n");
		i++;
	}
}

void	draw_player_vision(t_data *data)
{
	t_vector	center_map;
	t_vector	p_delta_posx;
	t_vector	p_delta_posx2;
	int			i;

	center_map = vec(data->minimap.UI_size / 2 + data->minimap.pos.x, data->minimap.UI_size / 2 + data->minimap.pos.y);
	//draw_square(data, center_map, linfo(0xFFb734eb, 4, data->check_shape[0]));
	draw_square(data, center_map, linfo(0xFFb734eb, 4, data->check_shape[0]));
	i = 0;
	while (i < NB_RAYS)
	{
		p_delta_posx.x = (data->player.vision[i].direc.x * data->player.vision[i].length) * (data->minimap.fig_size / (data->scale)) / 2 + center_map.x;
		p_delta_posx.y = (data->player.vision[i].direc.y * data->player.vision[i].length) * (data->minimap.fig_size / (data->scale)) / 2 + center_map.y;
		//draw_line(data, center_map, p_delta_posx, linfo(0xFF00FF00, 1, data->check_shape[1]));
		draw_line(data, center_map, p_delta_posx, linfo(0xFF00FF00, 1, data->check_shape[1]));
		i += 7;
	}
	// p_delta_posx.x = (data->player.vision[NB_RAYS / 2].direc.x * 10) * (data->minimap.fig_size / (data->scale)) / 2 + center_map.x;
	// p_delta_posx.y = (data->player.vision[NB_RAYS / 2].direc.y * 10) * (data->minimap.fig_size / (data->scale)) / 2 + center_map.y;
	// draw_line(data, center_map, p_delta_posx, linfo(0xFF00FF00, 3, data->check_shape[0]));
	// p_delta_posx.x = (data->player.camera_plane.x * 10) * (data->minimap.fig_size / (data->scale)) / 2 + center_map.x;
	// p_delta_posx.y = (data->player.camera_plane.y * 10) * (data->minimap.fig_size / (data->scale)) / 2 + center_map.y;
	// draw_line(data, center_map, p_delta_posx, linfo(0xFF0000FF, 3, data->check_shape[0]));
	// p_delta_posx.x = (-data->player.camera_plane.x * 10) * (data->minimap.fig_size / (data->scale)) / 2 + center_map.x;
	// p_delta_posx.y = (-data->player.camera_plane.y * 10) * (data->minimap.fig_size / (data->scale)) / 2 + center_map.y;
	// draw_line(data, center_map, p_delta_posx, linfo(0xFF0000FF, 3, data->check_shape[0]));
}

void	show_minimap(t_data *data)
{
	t_vector	i;

	// if (!data->minimap.img)
	// 	data->minimap.img = mlx_new_image(data->mlx, data->minimap.UI_size, data->minimap.UI_size);
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
	//mlx_put_image_to_window(data->mlx, data->win, data->minimap.pos.x, data->minimap.pos.y);
}

int	create_minimap(t_data *data, int UI_size, int fig_size)
{
	data->minimap.UI_size = UI_size;
	data->minimap.fig_size = fig_size;
	data->minimap.pos.x = 10;
	data->minimap.pos.y = 10;
	data->minimap.chunk_size = 0;
	data->minimap.chunk = NULL;
	if (!create_chunk_tab(&data->minimap))
		return (0);
	return (1);
}
