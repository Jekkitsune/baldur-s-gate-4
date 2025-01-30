/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strput.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:28:16 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 05:45:47 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_str_background(t_data *data)
{
	t_list		*lst;
	t_strput	*current_str;
	t_vector	size;
	t_vector	it;

	lst = data->string_to_put;
	while (lst)
	{
		current_str = lst->content;
		if (current_str->bg)
		{
			size.x = str_size(current_str->str, current_str->size);
			size.y = (current_str->size * 50) / 100;
			it.x = current_str->pos.x - 10;
			while (++it.x < size.x + current_str->pos.x + 15)
			{
				it.y = current_str->pos.y - 10 - size.y;
				while (++it.y < size.y + current_str->pos.y)
					ft_pixel_put(data, it.y, it.x, current_str->bg);
			}
		}
		lst = lst->next;
	}
}

size_t	str_size(char *str, float size)
{
	size_t	char_size;

	char_size = (size * 40) / 100;
	return (char_size * ft_strlen(str));
}

t_strput	*strput(char *str, t_vector pos, float size, uint32_t color)
{
	t_strput	*to_put;

	if (!str)
		return (NULL);
	to_put = ft_calloc(sizeof(t_strput), 1);
	if (!to_put)
	{
		if (str)
			free(str);
		return (NULL);
	}
	to_put->str = str;
	to_put->pos.x = pos.x;
	to_put->pos.y = pos.y;
	to_put->size = size;
	to_put->color = color;
	return (to_put);
}

int	screen_string_put(t_data *data, t_strput *to_put, float time)
{
	t_list			*lst;

	if (!to_put)
		return (0);
	if (to_put->centered)
		to_put->pos.x -= str_size(to_put->str, to_put->size) / 2;
	if (to_put->left)
		to_put->pos.x -= str_size(to_put->str, to_put->size);
	lst = ft_lstnew(to_put);
	if (!lst)
	{
		if (to_put->str)
			free(to_put->str);
		free(to_put);
		return (0);
	}
	if (time)
		to_put->duration = (float)time * 1000000.0;
	ft_lstadd_front(&data->string_to_put, lst);
	return (1);
}
