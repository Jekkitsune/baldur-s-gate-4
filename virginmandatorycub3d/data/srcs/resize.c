/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:23:58 by fparis            #+#    #+#             */
/*   Updated: 2025/01/17 00:55:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	average_color(uint32_t *col_tab, double len)
{
	uint32_t	alpha;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	int			i;

	i = 0;
	alpha = 0xFF;
	red = 0;
	green = 0;
	blue = 0;
	while (i < len)
	{
		if ((col_tab[i] >> 24) < alpha)
			alpha = col_tab[i] >> 24;
		red += ((col_tab[i] & 0x00FF0000) >> 16);
		green += ((col_tab[i] & 0x0000FF00) >> 8);
		blue += (col_tab[i] & 0x000000FF);
		i++;
	}
	red /= len;
	green /= len;
	blue /= len;
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

uint32_t	get_color(uint32_t *col_tab, uint32_t **tab, t_vectorf start,
	double size)
{
	t_vector	i;
	t_vectorf	end;
	int			col_tab_i;

	end.x = start.x + size;
	end.y = start.y + size;
	col_tab_i = 0;
	i.y = start.y;
	while (i.y < end.y)
	{
		i.x = start.x;
		while (i.x < end.x)
		{
			if (col_tab_i < ceil(size) * ceil(size))
				col_tab[col_tab_i] = tab[i.x][i.y];
			col_tab_i++;
			i.x++;
		}
		i.y++;
	}
	if (col_tab_i >= ceil(size) * ceil(size))
		col_tab_i = ceil(size) * ceil(size);
	return (average_color(col_tab, col_tab_i));
}

void	resize_loop(t_texture *tex, t_texture *res, uint32_t *col_tab,
	int new_size)
{
	t_vectorf	start;
	t_vector	i_tab;
	double		divided;

	divided = (double)tex->size / (double)new_size;
	i_tab.y = 0;
	start.y = 0;
	while (i_tab.y < new_size)
	{
		i_tab.x = 0;
		start.x = 0;
		while (i_tab.x < new_size)
		{
			res->tab[i_tab.x][i_tab.y]
				= get_color(col_tab, tex->tab, start, divided);
			i_tab.x++;
			start.x = divided * i_tab.x;
		}
		i_tab.y++;
		start.y = divided * i_tab.y;
	}
}

t_texture	*resize(t_texture *tex, int new_size)
{
	double		divided;
	t_texture	*res;
	uint32_t	*col_tab;

	res = new_texture(new_size);
	if (!res)
		return (NULL);
	divided = (double)tex->size / (double)new_size;
	if (divided >= 1)
		col_tab = ft_calloc(sizeof(uint32_t), ceil(divided) * ceil(divided));
	else
		col_tab = ft_calloc(sizeof(uint32_t), 4 + 1);
	if (!col_tab)
	{
		free_tex(res);
		return (NULL);
	}
	resize_loop(tex, res, col_tab, new_size);
	free(col_tab);
	return (res);
}

void	ft_pixel_put(t_data *data, int y, int x, uint32_t color)
{
	float		trans;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	if (x >= 0 && x < data->win_size.x && y >= 0 && y < data->win_size.y)
	{
		trans = (float)(color >> 24) / 255.0;
		red = (((data->screen_buffer[y][x] & 0x00FF0000) >> 16) * (1 - trans))
			+ (((color & 0x00FF0000) >> 16) * trans);
		green = (((data->screen_buffer[y][x] & 0x0000FF00) >> 8) * (1 - trans))
			+ (((color & 0x0000FF00) >> 8) * trans);
		blue = ((data->screen_buffer[y][x] & 0x000000FF) * (1 - trans))
			+ ((color & 0x000000FF) * trans);
		data->screen_buffer[y][x] = (0xFF << 24) | (red << 16) | (green << 8)
			| blue;
	}
}
