/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:23:58 by fparis            #+#    #+#             */
/*   Updated: 2024/10/03 03:01:23 by fparis           ###   ########.fr       */
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
	alpha = 0;
	red = 0;
	green = 0;
	blue = 0;
	while (i < len)
	{
		alpha += col_tab[i] >> 24;
		red += ((col_tab[i] & 0x00FF0000) >> 16);
		green += ((col_tab[i] & 0x0000FF00) >> 8);
		blue += (col_tab[i] & 0x000000FF);
		i++;
	}
	alpha /= len;
	red /= len;
	green /= len;
	blue /= len;
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

// uint32_t	color_weight(uint32_t **tab, t_vector i_tab, double weight)
// {
// 	uint32_t	alpha;
// 	uint32_t	red;
// 	uint32_t	green;
// 	uint32_t	blue;

// //	weight = 1;
// 	alpha = tab[i_tab.x][i_tab.y] >> 24;
// 	red = ((tab[i_tab.x][i_tab.y] & 0x00FF0000) >> 16) * weight;
// 	green = ((tab[i_tab.x][i_tab.y] & 0x0000FF00) >> 8) * weight;
// 	blue = (tab[i_tab.x][i_tab.y] & 0x000000FF) * weight;
// 	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
// }


// uint32_t	get_color_upscale(uint32_t *col_tab, uint32_t **tab, t_vectorf start, double size)
// {
// 	t_vector	i;
// 	t_vectorf	end;
// 	int			col_tab_i;
// 	int			nb_col;
// 	double		weight;

// 	end.x = start.x + size;
// 	end.y = start.y + size;
// 	i.x = start.x;
// 	i.y = start.y;
// 	col_tab[0] = color_weight(tab, i, weight);
// 	nb_col = 1;
// 	if (floor(start.x) != floor(end.x))
// 	{
// 		weight = (1 - (fmin(end.x, i.x + 1) - fmax(start.x, i.x))) * (fmin(end.y, i.y + 1) - fmax(start.y, i.y));
// 		col_tab[nb_col] = color_weight(tab, vec(floor(end.x), i.y), weight);
// 		nb_col++;
// 	}
// 	if (floor(start.y) != floor(end.y))
// 	{
// 		weight = (fmin(end.x, i.x + 1) - fmax(start.x, i.x)) * (1 - (fmin(end.y, i.y + 1) - fmax(start.y, i.y)));
// 		col_tab[nb_col] = color_weight(tab, vec(floor(end.x), i.y), weight);
// 		nb_col++;
// 	}
// 	if (nb_col == 3)
// 	{
// 		weight = (1 - (fmin(end.x, i.x + 1) - fmax(start.x, i.x))) * (1 - (fmin(end.y, i.y + 1) - fmax(start.y, i.y)));
// 		col_tab[nb_col] = color_weight(tab, vec(floor(end.x), i.y), weight);
// 		nb_col++; //important
// 	}
// 	return (average_color(col_tab, nb_col));
// }

uint32_t	get_color(uint32_t *col_tab, uint32_t **tab, t_vectorf start, double size)
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
			col_tab[col_tab_i] = tab[i.x][i.y];
			col_tab_i++;
			i.x++;
		}
		i.y++;
	}
	return (average_color(col_tab, col_tab_i));
}

t_texture	*resize(t_texture *tex, int new_size)
{
	double		divided;
	t_texture	*res;
	uint32_t	*col_tab;
	t_vectorf	start;
	t_vector	i_tab;

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
	i_tab.y = 0;
	start.y = 0;
	while (i_tab.y < new_size)
	{
		i_tab.x = 0;
		start.x = 0;
		while (i_tab.x < new_size)
		{
			res->tab[i_tab.x][i_tab.y] = get_color(col_tab, tex->tab, start, divided);
			i_tab.x++;
			start.x = divided * i_tab.x;
		}
		i_tab.y++;
		start.y = divided * i_tab.y;
	}
	return (res);
}
