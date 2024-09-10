/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:42:04 by fparis            #+#    #+#             */
/*   Updated: 2024/09/10 14:33:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_data *data, t_vector p1, t_vector p2, t_linfo info)
{
	t_vector	i;

	if (p1.y > p2.y)
		return (draw_vertical_line(data, p2, p1, info));
	i.x = p1.x;
	i.y = p1.y;
	while (i.y < p2.y)
	{
		draw_square(data, i, info);
		i.y++;
	}
}

void	draw_square(t_data *data, t_vector pos, t_linfo info)
{
	t_vector	i;
	t_vector	offset;

	offset.x = pos.x - (info.width / 2);
	offset.y = pos.y - (info.width / 2);
	i.y = 0;
	while (i.y < info.width)
	{
		i.x = 0;
		while (i.x < info.width)
		{
			//if (info.check(data, vec_sum(i, offset)))
				mlx_pixel_put(data->mlx, data->win, i.x + offset.x, i.y + offset.y, info.color);
			i.x++;
		}
		i.y++;
	}
}

void	draw_shallow(t_data *data, t_vector p1, t_vector p2, t_linfo info)
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
		draw_square(data, i, info);
		i.x++;
	}
}

void	draw_deep(t_data *data, t_vector p1, t_vector p2, t_linfo info)
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
		draw_square(data, i, info);
		i.y++;
	}
}

void	draw_line(t_data *data, t_vector p1, t_vector p2, t_linfo info)
{
	if (p1.x == p2.x)
		return (draw_vertical_line(data, p1, p2, info));
	if (ft_abs(p1.x - p2.x) >= ft_abs(p1.y - p2.y))
	{
		if (p1.x <= p2.x)
			draw_shallow(data, p1, p2, info);
		else
			draw_shallow(data, p2, p1, info);
	}
	else
	{
		if (p1.y <= p2.y)
			draw_deep(data, p1, p2, info);
		else
			draw_deep(data, p2, p1, info);
	}
}
