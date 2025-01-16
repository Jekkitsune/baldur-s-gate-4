/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:42:40 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 18:54:22 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_actbutton_name(t_data *data);

void	draw_button_img(t_data *data, t_texture *img, t_vector start)
{
	t_vector	i;

	i.x = 1;
	while (i.x < data->button_scale_size)
	{
		i.y = 1;
		while (i.y < data->button_scale_size)
		{
			ft_pixel_put(data, i.y + start.y, i.x + start.x,
				img->tab[i.x][i.y]);
			i.y++;
		}
		i.x++;
	}
}

void	draw_borders(t_data *data, t_vector start)
{
	t_vector	i;

	ft_pixel_put(data, start.y, start.x, 0xFF4a3b28);
	i.x = 0;
	while (i.x++ < data->button_scale_size)
	{
		ft_pixel_put(data, start.y, start.x + i.x, 0xFF4a3b28);
		ft_pixel_put(data, start.y + i.x, start.x, 0xFF4a3b28);
		ft_pixel_put(data, start.y + data->button_scale_size, start.x + i.x,
			0xFF4a3b28);
		ft_pixel_put(data, start.y + i.x, start.x + data->button_scale_size,
			0xFF4a3b28);
	}
}

void	draw_button(t_data *data, t_button button, t_vector start)
{
	t_vector	i;

	draw_borders(data, start);
	i.x = 1;
	while (i.x < data->button_scale_size)
	{
		i.y = 1;
		while (i.y < data->button_scale_size)
		{
			ft_pixel_put(data, i.y + start.y, i.x + start.x, 0xDD6B5333);
			i.y++;
		}
		i.x++;
	}
	if (button.active)
		draw_hover(data, start, 0xAA000000);
	if (button.img)
		draw_button_img(data, button.img, start);
}

t_vector	get_hover_pos(t_data *data, int margin)
{
	t_vector	mouse_pos;
	t_vector	res;

	res.x = -1;
	res.y = -1;
	mlx_mouse_get_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x > margin && mouse_pos.x < data->win_size.x - margin
		&& mouse_pos.y > data->win_size.y - (data->button_scale_size * 2) - 10
		&& mouse_pos.y < data->win_size.y - 10)
	{
		res.x = mouse_pos.x - margin;
		res.x = (res.x / data->button_scale_size) * data->button_scale_size
			+ margin;
		res.y = data->win_size.y - (data->button_scale_size * 2) - 10;
		if (mouse_pos.y > data->win_size.y - data->button_scale_size - 10)
			res.y += data->button_scale_size;
	}
	return (res);
}

void	draw_possession_button(t_data *data, t_button *buttons)
{
	int	i;
	int	margin;

	margin = (data->win_size.x - (data->button_scale_size * NB_BUTTON / 2)) / 2;
	if (margin > data->win_size.x || margin < 0)
		return ;
	i = -1;
	while (++i < NB_BUTTON / 2)
		draw_button(data, buttons[i], vec(margin + (i * \
		data->button_scale_size), data->win_size.y - \
		(data->button_scale_size * 2) - 10));
	i = -1;
	while (++i < NB_BUTTON / 2)
		draw_button(data, buttons[i + (NB_BUTTON / 2)], vec(margin + \
		(i * data->button_scale_size), data->win_size.y - \
		data->button_scale_size - 10));
	if (data->player.mouse_button[0])
		draw_hover(data, get_hover_pos(data, margin), 0x88000000);
	else
		draw_hover(data, get_hover_pos(data, margin), 0x44000000);
	draw_actbutton_name(data);
	if (data->player.active_button)
		show_action_cost(data, &data->player.active_button->spellinfo);
}
