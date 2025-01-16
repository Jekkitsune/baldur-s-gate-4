/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_draw_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:50:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 18:50:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_hover_index(t_data *data)
{
	t_vector	mouse_pos;
	int			res;
	int			margin;

	margin = (data->win_size.x - (data->button_scale_size * NB_BUTTON / 2)) / 2;
	res = -1;
	mlx_mouse_get_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x > margin && mouse_pos.x < data->win_size.x - margin
		&& mouse_pos.y > data->win_size.y - (data->button_scale_size * 2) - 10
		&& mouse_pos.y < data->win_size.y - 10)
	{
		res = mouse_pos.x - margin;
		res = (res / data->button_scale_size);
		if (mouse_pos.y > data->win_size.y - data->button_scale_size - 10)
			res += NB_BUTTON / 2;
	}
	return (res);
}

void	draw_hover(t_data *data, t_vector start, uint32_t color)
{
	t_vector	i;

	if (start.x < 0)
		return ;
	i.x = 1;
	while (i.x < data->button_scale_size)
	{
		i.y = 1;
		while (i.y < data->button_scale_size)
		{
			ft_pixel_put(data, i.y + start.y, i.x + start.x, color);
			i.y++;
		}
		i.x++;
	}
}

void	draw_actbutton_name(t_data *data)
{
	t_vector	mp;
	t_strput	*to_put;
	int			index;
	char		*name;
	char		*des;

	index = get_hover_index(data);
	if (index < 0)
		return ;
	name = data->player.possession->sheet.buttons[index].name;
	des = data->player.possession->sheet.buttons[index].description;
	if (!data->player.active_button)
		show_action_cost(data, &data->player.possession->sheet.\
			buttons[index].spellinfo);
	if (!name)
		return ;
	mlx_mouse_get_pos(data->mlx, &mp.x, &mp.y);
	to_put = strput(ft_strdup(name), vec(mp.x, mp.y - 10), 20, 0xFF000000);
	screen_string_put(data, to_put, 0);
	if (data->player.description_mode && des)
	{
		to_put = strput(ft_strdup(des), vec(mp.x, mp.y - 20), 20, 0xFF000000);
		screen_string_put(data, to_put, 0);
	}
}
