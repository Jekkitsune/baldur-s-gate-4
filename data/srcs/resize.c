/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:23:58 by fparis            #+#    #+#             */
/*   Updated: 2024/09/19 18:21:11 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	average_color(uint32_t *col_tab, uint32_t *val_tab, int len)
{
	uint32_t	alpha;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	int			i;

	i = 0;
	alpha = 0;
	red = 0;
	while (i < len)
	{
		alpha += col_tab[i] >> 24;
		red += ((col_tab[i] & 0x00FF0000) >> 16) * val_tab[i];
		green += ((col_tab[i] & 0x0000FF00) >> 8) * val_tab[i];
		blue = (col_tab[i] & 0x000000FF) * val_tab[i];
		i++;
	}
	alpha /= len;
	red /= len;
	green /= len;
	blue /= len;
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

t_texture	*upscale(t_texture *tex, int new_size)
{
	float		divided;
	int			i;
	uint32_t	*col_tab;
	uint32_t	*val_tab;
	t_texture	*res;

	res = ft_calloc(sizeof())
	divided = tex->size / new_size;
	i = 0;

	return (tex);
}

t_texture	*downscale(t_texture *tex, int new_size)
{
	return (tex);
}

t_texture	*resize(t_texture *tex, int new_size)
{
	if (new_size > tex->size)
		return (upscale(tex, new_size));
	return (downscale(tex, new_size));
}
