/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_hate_dice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:05:18 by fparis            #+#    #+#             */
/*   Updated: 2025/01/07 11:49:09 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_point(t_data *data, t_vector pos, uint32_t color, int size)
{
	int	i;
	int	i2;

	i = 0;
	while (i < size)
	{
		i2 = 0;
		while (i2 < size)
		{
			ft_pixel_put(data, pos.y + i2 + 1, pos.x + i + 1, color);
			i2++;
		}
		i++;
	}
}

void	draw_row(t_data *data, t_vector base_pos, int nb_point, uint32_t color)
{
	int			diff;
	int			size;
	int			i;
	t_vector	pos;

	if (nb_point <= 0)
		return ;
	size = data->button_scale_size / 4;
	diff = (data->button_scale_size - (size * nb_point)) / (nb_point + 1);
	i = 0;
	pos = base_pos;
	while (i < nb_point)
	{
		pos.x += diff;
		draw_point(data, pos, color, size);
		pos.x += size;
		i++;
	}
}

void	get_good_tab(int tab[3], int nb_point)
{
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	if (nb_point == 2 || nb_point == 4 || nb_point == 6)
		tab[0] = 2;
	else
		tab[0] = 3;
	if (nb_point == 4 || nb_point == 6)
		tab[1] = 2;
	if (nb_point == 5)
	{
		tab[1] = 1;
		tab[2] = 3;
	}
	if (nb_point == 6)
		tab[2] = 2;
}

void	draw_one_point(t_data *data, t_vector pos, uint32_t color)
{
	int			size;
	int			row_diff;

	size = data->button_scale_size / 3;
	row_diff = (data->button_scale_size - size) / 2;
	draw_point(data, vec(pos.x + (data->button_scale_size / 2) - (size / 2), pos.y + row_diff), color, size);
}

void	draw_box_points(t_data *data, t_vector pos, int nb_point, uint32_t color)
{
	int			row;
	int			row_diff;
	int			size;
	int			tab[3];
	int			i;

	if (!nb_point)
		return ;
	if (nb_point == 1)
		return (draw_one_point(data, pos, color));
	row = 1 + (nb_point >= 4) + (nb_point >= 5);
	size = data->button_scale_size / 4;
	if (!size)
		size = 1;
	row_diff = (data->button_scale_size - (size * row)) / (row + 1);
	get_good_tab(tab, nb_point); 
	i = 0;
	while (tab[i] && i < 3)
	{
		pos.y += row_diff;
		draw_row(data, pos, tab[i], color);
		pos.y += size;
		i++;
	}
}
