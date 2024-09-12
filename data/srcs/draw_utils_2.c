/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:54:47 by fparis            #+#    #+#             */
/*   Updated: 2024/09/12 18:54:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	reverse_draw_vertical_line(t_data *data, t_vector p1, t_vector p2, t_linfo info)
{
	t_vector	i;

	i.x = p1.x;
	i.y = p1.y;
	while (i.y > p2.y && info.check(data, i))
	{
		draw_square(data, i, info);
		i.y--;
	}
}

void	reverse_draw_shallow(t_data *data, t_vector p1, t_vector p2, t_linfo info)
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
	while (i.x >= p2.x && info.check(data, i))
	{
		if (checker > 0)
		{
			i.y += y_diff;
			checker += (2 * delta.y) - (2 * delta.x);
		}
		else
			checker += 2 * delta.y;
		draw_square(data, i, info);
		i.x--;
	}
}

void	reverse_draw_deep(t_data *data, t_vector p1, t_vector p2, t_linfo info)
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
	while (i.y >= p2.y && info.check(data, i))
	{
		if (checker > 0)
		{
			i.x += x_diff;
			checker += (2 * delta.x) - (2 * delta.y);
		}
		else
			checker += 2 * delta.x;
		draw_square(data, i, info);
		i.y--;
	}
}