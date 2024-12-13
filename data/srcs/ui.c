/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:55:51 by fparis            #+#    #+#             */
/*   Updated: 2024/12/13 18:51:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(t_data *data, t_vector start, t_vector end, uint32_t color)
{
	int	i;
	int	i2;

	i = start.x;
	while (i < end.x)
	{
		i2 = start.y;
		while (i2 < end.y)
		{
			ft_pixel_put(data, i2, i, color);
			i2++;
		} 
		i++;
	}
}

void	show_health_bar(t_data *data)
{
	t_entity	*selected;
	t_vector	limit;
	int			empty_side;
	int			size;
	int			width;

	selected = NULL;
	if (data->player.arrow)
		selected = cycle_entity_cell(data, 0);
	if (!selected || !selected->sheet.max_hp)
		return ;
	size = data->button_scale_size * 8;
	width = data->button_scale_size;
	limit.x = data->win_size.x / 2 - (size / 2);
	limit.y = data->win_size.x / 2 + (size / 2);
	if (selected->sheet.name)
	{
		draw_rectangle(data, vec((data->win_size.x / 2) - (ft_strlen(selected->sheet.name) * 6), 1),
			vec((data->win_size.x / 2) + (ft_strlen(selected->sheet.name) * (data->button_scale_size / 3)), data->button_scale_size - 2), 0xAA000000);
		screen_string_put(data, strput(ft_strdup(selected->sheet.name), vec((data->win_size.x / 2)
			- (ft_strlen(selected->sheet.name) * 5),
				data->button_scale_size - 10), data->button_scale_size, 0xFFAAAAAA));
	}
	empty_side = selected->sheet.hp * size / selected->sheet.max_hp + limit.x;
	if (empty_side < limit.x)
		empty_side = limit.x;
	draw_rectangle(data, vec(limit.x, data->button_scale_size), vec(empty_side, data->button_scale_size + width), 0xFFD44242);
	if (empty_side < limit.y)
		draw_rectangle(data, vec(empty_side, data->button_scale_size), vec(limit.y, data->button_scale_size + width), 0xAA702222);
}
