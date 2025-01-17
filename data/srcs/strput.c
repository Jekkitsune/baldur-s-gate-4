/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strput.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:28:16 by fparis            #+#    #+#             */
/*   Updated: 2025/01/17 00:28:41 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
