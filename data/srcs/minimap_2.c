/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:44:16 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 12:32:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	create_chunk_tab(t_minimap *minimap)
{
	int	i;	

	minimap->chunk_size = (minimap->ui_size / minimap->fig_size) + 2;
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
				data->minimap.chunk[i_chunk.x][i_chunk.y] = data->current_map->\
				arr[i_map.x + i_chunk.x][i_map.y + i_chunk.y].type;
			else
				data->minimap.chunk[i_chunk.x][i_chunk.y] = 0;
			i_chunk.x++;
		}
		i_chunk.y++;
	}
}
