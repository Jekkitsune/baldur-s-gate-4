/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:52:10 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:32:15 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_fog	*new_fog(t_data *data, t_impact *ray, float fog_length)
{
	t_fog	*new_fog;

	new_fog = ft_calloc(sizeof(t_fog), 1);
	if (!new_fog)
		return (NULL);
	new_fog->cell = &data->current_map->arr[ray->wall_pos.x][ray->wall_pos.y];
	new_fog->i = ray->i;
	new_fog->fog_color = new_fog->cell->fog_color;
	new_fog->length = fog_length;
	new_fog->next = NULL;
	return (new_fog);
}

void	sort_fog(t_data *data, t_impact *ray, float fog_length)
{
	t_fog	*new;
	t_fog	*i;

	new = new_fog(data, ray, fog_length);
	if (!new)
		return ;
	i = data->player.visible_fog;
	if (!i || i->length <= new->length)
	{
		new->next = data->player.visible_fog;
		data->player.visible_fog = new;
		return ;
	}
	while (i->next && i->next->length > new->length)
		i = i->next;
	new->next = i->next;
	i->next = new;
}

void	draw_fog_wall(t_data *data, int x, t_vector pos, uint32_t color)
{
	int	i;

	i = 0;
	i = ft_max(pos.x, i);
	while (i < pos.y && i < data->win_size.y)
	{
		if (i >= 0)
			ft_pixel_put(data, i, x, color);
		i++;
	}
}

void	draw_fog(t_data *data, float diff, t_fog *fog)
{
	int			i2;
	int			size;
	t_vector	posy;

	if (fog->length <= 0)
		return ;
	if (fog->cell && fog->cell->fog_color)
		fog->cell->fog_color = 0;
	size = (data->win_size.y / (fog->length / (data->scale * 2)));
	posy.x = (data->win_size.y - size) / 2;
	posy.y = (data->win_size.y + size) / 2;
	i2 = 0;
	while (i2 < diff)
	{
		draw_fog_wall(data, fog->i * diff + i2, vec(posy.x + data->player.pitch \
		+ (data->player.height / fog->length), posy.y + data->player.pitch \
		+ (data->player.height / fog->length)), fog->fog_color);
		i2++;
	}
}
