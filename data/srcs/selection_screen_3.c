/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_screen_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:25:29 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 13:26:10 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_bg(t_data *data, int size, t_vector pos, uint32_t color)
{
	int	i;
	int	j;

	i = pos.x;
	while (i < pos.x + size)
	{
		j = pos.y;
		while (j < pos.y + size)
		{
			data->screen_buffer[j][i] = color;
			j++;
		}
		i++;
	}
}

int	is_selected(t_data *data, char *class, t_vector pos, int size)
{
	t_vector	mouse;

	mlx_mouse_get_pos(data->mlx, &mouse.x, &mouse.y);
	if (in_party_name(data, class))
		return (2);
	else if (mouse.x < pos.x || mouse.x > pos.x + size
		|| mouse.y < pos.y || mouse.y > pos.y + size)
		return (0);
	else
		return (1);
}

void	draw_border(t_data *data, t_vector pos, int size, uint32_t color)
{
	int	i;
	int	j;

	i = pos.x - 2;
	while (i < pos.x + size + 2)
	{
		j = pos.y - 2;
		while (j < pos.y + size + 2)
		{
			ft_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}

void	chose_border(t_data *data, t_bool selected, int size, t_vector pos)
{
	if (!selected)
		draw_bg(data, size, pos, 0xFF232323);
	else if (selected == 1)
	{
		draw_border(data, pos, size, 0xFFFFFFFF);
		draw_bg(data, size, pos, 0xFF303030);
	}
	else
	{
		draw_border(data, pos, size, 0xFFE6C302);
		draw_bg(data, size, pos, 0xFF353535);
	}
}
