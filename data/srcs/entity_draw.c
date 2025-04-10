/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:26:54 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:27:30 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		entity_face(t_data *data, t_entity *entity);
void	draw_entity_dialog(t_data *data, t_entity *entity);

uint32_t	average_filter(uint32_t color1, uint32_t color2)
{
	uint32_t	alpha;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	alpha = ((color1 >> 24) + (color2 >> 24)) / 2;
	red = (((color1 & 0x00FF0000) >> 16) + ((color2 & 0x00FF0000) >> 16)) / 2;
	green = (((color1 & 0x0000FF00) >> 8) + ((color2 & 0x0000FF00) >> 8)) / 2;
	blue = ((color1 & 0x000000FF) + (color2 & 0x000000FF)) / 2;
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

t_texture	*apply_filter(t_texture *tex, uint32_t filter)
{
	t_texture	*res;
	int			i;
	int			i2;

	if (!tex)
		return (NULL);
	res = new_texture(tex->size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < tex->size)
	{
		i2 = 0;
		while (i2 < tex->size)
		{
			if (tex->tab[i][i2] >> 24)
				res->tab[i][i2] = average_filter(tex->tab[i][i2], filter);
			i2++;
		}
		i++;
	}
	return (res);
}

void	draw_entity_tex(t_data *data, t_entity *entity, t_texture *tex)
{
	t_vector	i;
	t_vector	size;
	int			i_tab;

	size.x = entity->draw_x.y - entity->draw_x.x;
	size.y = entity->draw_y.y - entity->draw_y.x;
	i.x = ft_max(entity->draw_x.x, 0);
	while (tex && i.x < entity->draw_x.y && i.x < data->win_size.x)
	{
		if (((i.x * NB_RAYS) / WIDTH) < NB_RAYS && ((i.x * NB_RAYS) / WIDTH) > 0
			&& data->player.vision[(i.x * NB_RAYS) / WIDTH].length
			< entity->distance)
		{
			i.x++;
			continue ;
		}
		i.y = ft_max(entity->draw_y.x, 0) - 1;
		i_tab = (i.x - entity->draw_x.x) * tex->size / size.x;
		while (++i.y < entity->draw_y.y && i.y < data->win_size.y)
			ft_pixel_put(data, i.y, i.x,
				tex->tab[i_tab][(i.y - entity->draw_y.x) * tex->size / size.y]);
		i.x++;
	}
}

void	draw_entity(t_data *data, t_entity *entity)
{
	int			face;
	t_texture	*filtered;

	if (!entity || entity->draw_x.x == data->win_size.x
		|| dont_draw(data, entity))
		return ;
	face = entity_face(data, entity);
	if (!entity->color_filter)
		draw_entity_tex(data, entity, get_correct_tex(entity, face));
	else
	{
		filtered = apply_filter(get_correct_tex(entity, face),
				entity->color_filter);
		draw_entity_tex(data, entity, filtered);
		free_tex(filtered);
		entity->color_filter = 0;
	}
	draw_entity_dialog(data, entity);
}
