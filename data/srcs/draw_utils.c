/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:42:04 by fparis            #+#    #+#             */
/*   Updated: 2024/08/28 17:56:07 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_data *data, t_vector p1, t_vector p2, t_vector col_width)
{
	t_vector	i;

	if (p1.y > p2.y)
		return (draw_vertical_line(data, p2, p1, col_width));
	i.x = p1.x;
	i.y = p1.y;
	while (i.y < p2.y)
	{
		draw_square(data, i, col_width);
		i.y++;
	}
}

void	draw_square(t_data *data, t_vector pos, t_vector col_width)
{
	t_vector	i;
	t_vector	offset;

	offset.x = pos.x - (col_width.y / 2);
	offset.y = pos.y - (col_width.y / 2);
	i.y = 0;
	while (i.y < col_width.y)
	{
		i.x = 0;
		while (i.x < col_width.y)
		{
			mlx_pixel_put(data->mlx, data->win, i.x + offset.x, i.y + offset.y, col_width.x);
			i.x++;
		}
		i.y++;
	}
}

void	draw_shallow(t_data *data, t_vector p1, t_vector p2, t_vector col_width)
{
	int			y_diff;
	t_vector	delta;
	t_vector	i;
	int			checker;

	y_diff = 1;
	if (p1.y > p2.y)
		y_diff = -1;
	delta.x = ft_abs(p2.x - p1.x);
	delta.y = ft_abs(p2.y - p1.y);
	i.x = p1.x;
	i.y = p1.y;
	checker = (2 * delta.y) - delta.x; 
	while (i.x <= p2.x)
	{
		if (checker > 0)
		{
			i.y += y_diff;
			checker += (2 * delta.y) - (2 * delta.x);
		}
		else
			checker += 2 * delta.y;
		draw_square(data, i, col_width);
		i.x++;
	}
}

void	draw_deep(t_data *data, t_vector p1, t_vector p2, t_vector col_width)
{
	int			x_diff;
	t_vector	delta;
	t_vector	i;
	int			checker;

	x_diff = 1;
	if (p1.x > p2.x)
		x_diff = -1;
	delta.x = ft_abs(p2.x - p1.x);
	delta.y = ft_abs(p2.y - p1.y);
	i.x = p1.x;
	i.y = p1.y;
	checker = (2 * delta.x) - delta.y;
	while (i.y <= p2.y)
	{
		if (checker > 0)
		{
			i.x += x_diff;
			checker += (2 * delta.x) - (2 * delta.y);
		}
		else
			checker += 2 * delta.x;
		draw_square(data, i, col_width);
		i.y++;
	}
}

void	draw_line(t_data *data, t_vector p1, t_vector p2, t_vector col_width)
{
	if (p1.x == p2.x)
		return (draw_vertical_line(data, p1, p2, col_width));
	if (ft_abs(p1.x - p2.x) >= ft_abs(p1.y - p2.y))
	{
		if (p1.x <= p2.x)
			draw_shallow(data, p1, p2, col_width);
		else
			draw_shallow(data, p2, p1, col_width);
	}
	else
	{
		if (p1.y <= p2.y)
			draw_deep(data, p1, p2, col_width);
		else
			draw_deep(data, p2, p1, col_width);
	}
}
